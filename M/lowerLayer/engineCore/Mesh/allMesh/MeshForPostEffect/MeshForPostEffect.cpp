#include "MeshForPostEffect.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>

void MeshForPostEffect::CreateMesh(ID3D12Device* device_)
{
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer =
		static_cast<UINT>(sizeof(Vertex) * 6 * kMax);
	// 頂点バッファ生成
	vertexBuffer.Create(device_, sizeOfVertexBuffer);
	// 頂点バッファのマッピング
	HRESULT result = vertexBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));
}

MeshForPostEffect::MeshForPostEffect(ID3D12Device* device_, AllPipelineSet* allPipelineset_)
{
	CreateMesh(device_);
	CreatePSO(allPipelineset_);
}

void MeshForPostEffect::CreatePSO(AllPipelineSet* allPipelineset_)
{
	static bool onlyOnce = true;

	if (onlyOnce)
	{
		onlyOnce = false;

		auto inputLayOutFunc = []()
			{
				std::vector<D3D12_INPUT_ELEMENT_DESC> descs;
				descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
					"POSITION",
					0,
					DXGI_FORMAT_R32G32B32_FLOAT,
					D3D12_APPEND_ALIGNED_ELEMENT
				));

				descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
					"TEXCOORD",
					0,
					DXGI_FORMAT_R32G32_FLOAT,
					D3D12_APPEND_ALIGNED_ELEMENT
				));

				return descs;

			};

		auto rootparameterMonoChrome = []() {

			std::vector<D3D12_ROOT_PARAMETER> meters;
			meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 0));
			meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::VS, 0));

			return meters;
			};


		std::string folderPath = "PostEffect/";

		allPipelineset_->CreateNewPipeline(folderPath, "MonoChrome.VS", "MonoChrome.PS", inputLayOutFunc, rootparameterMonoChrome);
	}
}
