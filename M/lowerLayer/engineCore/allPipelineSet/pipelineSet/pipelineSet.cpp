#include "PipelineSet.h"
#include <assert.h>
#include "../../WinApp.h"

#pragma comment(lib,"d3d12.lib")


void PipelineSet::Activate_InputLayoutCreateFunc(std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> func_)
{
	pipelineCreators.inputLayoutCreator.AddToFuncs_InputElementDescsCreate(func_);
}

void PipelineSet::Activate_RootparameterCreateFunc(std::function<std::vector<D3D12_ROOT_PARAMETER>()> func_)
{
	pipelineCreators.rootSignatureCreator.AddToFuncs_RootParametersCreate(func_);
}


[[nodiscard]] std::unique_ptr<PipelineSet> PipelineSet::CreateGraphicsPipelineSet(ID3D12Device* device_,
	std::string shaderSetName_,
	VPShaderTable* vpShaderTable_,
	BlendMode blendMode_,
	CullMode cullMode_,
	bool isTopologyLine)
{
	//return 
	std::unique_ptr<PipelineSet> ret_pipelineSet = std::make_unique<PipelineSet>();
	//graphiscPipelineDesc
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graghicsPipeLineStatedesc{};
	int shaderSetIndex = vpShaderTable_->GetIDFromTableName(shaderSetName_);

	//==============================================================================================
	//PrimitiveTopologyType
	//==============================================================================================
	if (isTopologyLine)
	{
		graghicsPipeLineStatedesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
	}
	else
	{
		graghicsPipeLineStatedesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}


	//==============================================================================================
	//ShaderBlobSet
	//==============================================================================================
	//vertexShaderBlob
	IDxcBlob* srcVertexShaderBlob = vpShaderTable_->Getter_ShaderTable()[shaderSetName_].verShaderBlob;

	//pixelShaderBlob
	IDxcBlob* srcPixelShaderBlob = vpShaderTable_->Getter_ShaderTable()[shaderSetName_].pixShaderBlob;

	//shaderBlobをセット(Vertex)
	graghicsPipeLineStatedesc.VS =
	{
		srcVertexShaderBlob->GetBufferPointer(),
		srcVertexShaderBlob->GetBufferSize()
	};
	//shaderBlobをセット(Pixel)
	graghicsPipeLineStatedesc.PS =
	{
		srcPixelShaderBlob->GetBufferPointer(),
		srcPixelShaderBlob->GetBufferSize()
	};


	//==============================================================================================
	//RootSignature
	//==============================================================================================
	ret_pipelineSet->rootSignature = pipelineCreators.rootSignatureCreator.CreateRootSignature(
	device_,
	shaderSetIndex,
	shaderSetName_);

	graghicsPipeLineStatedesc.pRootSignature = ret_pipelineSet->rootSignature.Get();
	//rootparameterを記録しておく
	pipelineCreators.rootSignatureCreator.RecordRootparameters(ret_pipelineSet->rootParameters, shaderSetIndex);

	//==============================================================================================
	//InputLayout
	//==============================================================================================
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc = pipelineCreators.inputLayoutCreator.CreateInputLayoutDesc(shaderSetIndex);
	graghicsPipeLineStatedesc.InputLayout = inputLayoutDesc;

	//==============================================================================================
	//blendMode
	//==============================================================================================
	D3D12_BLEND_DESC blendDesc{};
	blendDesc = pipelineCreators.blendDescCreator.CreateBlendDesc(blendMode_);
	graghicsPipeLineStatedesc.BlendState = blendDesc;


	//==============================================================================================
	//RasterizerState
	//==============================================================================================
	D3D12_RASTERIZER_DESC rasterizerDesc = pipelineCreators.rasterizerDescCreator.CreateRasterizerDesc(cullMode_);
	graghicsPipeLineStatedesc.RasterizerState = rasterizerDesc;


	//書き込むRTVの情報
	graghicsPipeLineStatedesc.NumRenderTargets = 1;
	graghicsPipeLineStatedesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//どのようにして色を打ち込むかの設定
	graghicsPipeLineStatedesc.SampleDesc.Count = 1;
	graghicsPipeLineStatedesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	//==============================================================================================
	//DepthStencilState
	//==============================================================================================
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc = pipelineCreators.depthStencilDescCreator.CreateDepthStencilDesc(blendMode_);

	graghicsPipeLineStatedesc.DepthStencilState = depthStencilDesc;
	graghicsPipeLineStatedesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;



	//実際に生成
	HRESULT hr = device_->CreateGraphicsPipelineState(&graghicsPipeLineStatedesc,
		IID_PPV_ARGS(&ret_pipelineSet->pipelineStateObject));

	assert(SUCCEEDED(hr));
	Log(WinApp::log, shaderSetName_+" _graghicsPipelineState\n");


	//諸所リセット
	pipelineCreators.SafeReset();

	return ret_pipelineSet;
}


