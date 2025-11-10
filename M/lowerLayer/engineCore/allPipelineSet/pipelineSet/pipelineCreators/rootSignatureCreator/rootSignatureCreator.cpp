#include "rootSignatureCreator.h"
#include <assert.h>
#include "../../../../WinApp.h"

#pragma comment(lib,"d3d12.lib")

std::pair<D3D12_ROOT_PARAMETER*,UINT> RootSignatureCreator::GetRootParameters(std::string shaderSetName_)
{
	std::pair<D3D12_ROOT_PARAMETER*, UINT> ret;

	D3D12_ROOT_PARAMETER* heap_rootParameters = nullptr;
	UINT numRootParameters = 0;

	if (shaderSetName_ == "Default,Default")
	{
		numRootParameters = 5;

		heap_rootParameters = new D3D12_ROOT_PARAMETER[numRootParameters];

		//Descriptortableを使う
		heap_rootParameters[0] = GetRootParaMeterDescriptorRange();
		//WorldMatrix
		heap_rootParameters[1] = GetRootParaMeterVertexShader(0);
		//CameraPara
		heap_rootParameters[2] = GetRootParaMeterVertexShader(1);

		//Material
		heap_rootParameters[3] = GetRootParaMeterPixelShader(2);
		//DirectionalLight
		heap_rootParameters[4] = GetRootParaMeterPixelShader(3);
	}

	ret.first = heap_rootParameters;
	ret.second = numRootParameters;

	return ret;
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

D3D12_ROOT_PARAMETER RootSignatureCreator::GetRootParaMeterDescriptorRange()
{
	D3D12_ROOT_PARAMETER ret_rootParameter = {};

	//descriptorRange[0] = GetShaderViewDescriptorRange();
	//0から始まる
	descriptorRange[0].BaseShaderRegister = 0;
	//数は1つ
	descriptorRange[0].NumDescriptors = 1;
	//SRVを使う
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	//offsetを自動計算
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//Descriptortableを使う
	ret_rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	//pixcelShaderを使う
	ret_rootParameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//tableの中身の配列を指定
	ret_rootParameter.DescriptorTable.pDescriptorRanges = descriptorRange;
	//tableで利用する
	ret_rootParameter.DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);


	return ret_rootParameter;

}

[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12RootSignature> RootSignatureCreator::CreateRootSignature(
	ID3D12Device* device_,
	std::string shaderSetName_)
{
	Microsoft::WRL::ComPtr<ID3D12RootSignature> ret_rootSignature = nullptr;

	D3D12_ROOT_SIGNATURE_DESC signatureDesc = {};

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};

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


	std::pair<D3D12_ROOT_PARAMETER*, UINT> rootParameters = GetRootParameters(shaderSetName_);

	//ルートパラメータ配列へのポインタ
	signatureDesc.pParameters = rootParameters.first;
	//配列の長さ
	signatureDesc.NumParameters = rootParameters.second;
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
	delete[] rootParameters.first;

	return ret_rootSignature;
}
