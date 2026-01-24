#include "MeshForPostEffect.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>
#include"../../../commonVariables.h"

void MeshForPostEffect::CreateMesh(ID3D12Device* device_)
{
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer =
		static_cast<UINT>(sizeof(Vertex) * kVertexCnt);
	// 頂点バッファ生成
	vertexBuffer.Create(device_, sizeOfVertexBuffer);
	// 頂点バッファのマッピング
	HRESULT result = vertexBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));

	vertexMap[0].position = { 0.0f,CommonV::kWindow_H,0.0f };
	vertexMap[1].position = { 0.0f,0.0f,0.0f };
	vertexMap[2].position = { CommonV::kWindow_W,0.0f,0.0f };
	vertexMap[3].position = { CommonV::kWindow_W,CommonV::kWindow_H,0.0f };

	vertexMap[0].texcoord = { 0.0f,1.0f};
	vertexMap[1].texcoord = { 0.0f,0.0f};
	vertexMap[2].texcoord = { 1.0f,0.0f};
	vertexMap[3].texcoord = { 1.0f,1.0f};


	// インデックスデータのサイズ
	UINT sizeOfIndexBuffer = static_cast<UINT>(sizeof(uint32_t) * kIndexCnt * kMax);
	indexBuffer.Create(device_, sizeOfIndexBuffer);
	// インデックスバッファのマッピング
	result = indexBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&indexMap));
	assert(SUCCEEDED(result));

	for (int i = 0; i < kMax; i+= kIndexCnt)
	{
		indexMap[i] = 1;
		indexMap[i + 1] = 0;
		indexMap[i + 2] = 3;

		indexMap[i + 3] = 1;
		indexMap[i + 4] = 3;
		indexMap[i + 5] = 2;

	}

}

MeshForPostEffect::MeshForPostEffect(ID3D12Device* device_, AllPipelineSet* allPipelineset_)
{
	CreateMesh(device_);
	CreatePSO(allPipelineset_);
}

void MeshForPostEffect::CreatePSO(AllPipelineSet* allPipelineset_)
{
	static bool onlyOnce = true;
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
	allPipelineset_->CreateNewPipeline(folderPath, "NoEffection.VS", "NoEffection.PS", inputLayOutFunc, rootparameterMonoChrome);

}
