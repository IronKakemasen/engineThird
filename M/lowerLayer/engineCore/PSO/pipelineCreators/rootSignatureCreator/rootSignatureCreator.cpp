#include "rootSignatureCreator.h"
#include "../../../WinApp.h"
#include "../../allPipelineSet.h"
#include <assert.h>

#pragma comment(lib,"d3d12.lib")


void RootSignatureCreator::CopyFromIndex(int funcIndex_)
{
	std::vector<D3D12_ROOT_PARAMETER> rootParameters = funcs_rootParametersCreate[funcIndex_]();
	heap_rootParametersAndSum.second = UINT(rootParameters.size());
	heap_rootParametersAndSum.first = new D3D12_ROOT_PARAMETER[heap_rootParametersAndSum.second];

	int index = 0;
	for (auto itr = rootParameters.begin(); itr != rootParameters.end(); ++itr, index++)
	{
		heap_rootParametersAndSum.first[index] = (*itr);
	}
}

void RootSignatureCreator::AddToFuncs_RootParametersCreate(std::function<std::vector<D3D12_ROOT_PARAMETER>()> func_)
{
	sum_created++;
	if (sum_created >= AllPipelineSet::kNumShaderSet) assert(false);

	funcs_rootParametersCreate.emplace_back(func_);
}

void RootSignatureCreator::SetRootParameters(int index_)
{
	CopyFromIndex(index_);
}

D3D12_ROOT_PARAMETER RootSignatureCreator::GetRootParaMeterPixelShader(int registerNum_)
{
	D3D12_ROOT_PARAMETER ret_rootParameter = {};

	ret_rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	//PixcelShaderで使う
	ret_rootParameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//レジスタ番号0とバインド
	ret_rootParameter.Descriptor.ShaderRegister = registerNum_;

	return ret_rootParameter;
}

D3D12_ROOT_PARAMETER RootSignatureCreator::GetRootParaMeterVertexShader(int registerNum_)
{
	D3D12_ROOT_PARAMETER ret_rootParameter = {};

	ret_rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	//PixcelShaderで使う
	ret_rootParameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	//レジスタ番号0とバインド
	ret_rootParameter.Descriptor.ShaderRegister = registerNum_;

	return ret_rootParameter;

}


void RootSignatureCreator::SetDescriptorRange(D3D12_DESCRIPTOR_RANGE* dst_,
	D3D12_DESCRIPTOR_RANGE_TYPE rangeType_,
	int registerNum_)
{
	dst_->BaseShaderRegister = registerNum_;
	//数は1つ
	dst_->NumDescriptors = 1;
	//SRVを使う
	dst_->RangeType = rangeType_;
	//offsetを自動計算
	dst_->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

D3D12_ROOT_PARAMETER RootSignatureCreator::GetRootParameterWithDescriptorRange(
	D3D12_DESCRIPTOR_RANGE* descriptorRange_,
	D3D12_SHADER_VISIBILITY visibility_,
	UINT numDescriptors_)
{
	D3D12_ROOT_PARAMETER ret_rootParameter = {};
	//Descriptortableを使う
	ret_rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	//pixcelShaderを使う
	ret_rootParameter.ShaderVisibility = visibility_;
	//tableの中身の配列を指定
	ret_rootParameter.DescriptorTable.pDescriptorRanges = descriptorRange_;
	//tableで利用する
	ret_rootParameter.DescriptorTable.NumDescriptorRanges = numDescriptors_;

	return ret_rootParameter;
}



[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignatureCreator::CreateRootSignature(
	ID3D12Device* device_,
	int index_,
	std::string shaderSetName_)
{
	Microsoft::WRL::ComPtr<ID3D12RootSignature> ret_rootSignature = nullptr;

	D3D12_ROOT_SIGNATURE_DESC signatureDesc = {};

	//バイリニアフィルター
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	//0～1の範囲外をリピート
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	//比較しない
	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	//ありったけのmipMapを使う
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	//レジスタ番号0を使う
	staticSamplers[0].ShaderRegister = 0;
	//PixcelShaderで使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	signatureDesc.pStaticSamplers = staticSamplers;
	signatureDesc.NumStaticSamplers = _countof(staticSamplers);

	//std::pair<D3D12_ROOT_PARAMETER*, UINT> rootParameters = GetRootParameters(shaderSetName_);
	SetRootParameters(index_);

	//ルートパラメータ配列へのポインタ
	signatureDesc.pParameters = heap_rootParametersAndSum.first;
	//配列の長さ
	signatureDesc.NumParameters = heap_rootParametersAndSum.second;
	//pixcelShaderで読むConstantBufferのBind情報を追加する
	signatureDesc.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	//シリアライズしてバイナリにする
	HRESULT hr = D3D12SerializeRootSignature(
		&signatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));

		assert(false);
	}

	//バイナリをもとにrootSignatureを作成
	hr = device_->CreateRootSignature(0,
		signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(ret_rootSignature.GetAddressOf()));

	assert(SUCCEEDED(hr));
	Log(WinApp::log, shaderSetName_+" : Complete create rootSignature\n");

	//解放
	delete[] heap_rootParametersAndSum.first;

	return ret_rootSignature;
}


