#include "LineMesh.h"
#include <assert.h>
#include <wrl.h>
#include <d3d12.h>
#include "../../../PSO/allPipelineSet.h"

LineMesh::LineMesh(AllPipelineSet* allPipelineset_, ID3D12Device* device_)
{
	CreateMesh(device_);
	Init(MaxDraw::kLineMax, allPipelineset_);
}

void LineMesh::Init(uint16_t maxDraw_, AllPipelineSet* allPipelineset_)
{
	maxDraw = maxDraw_;
	materialForLineBuffers.resize(maxDraw_);
	CreatePSO(allPipelineset_);
}

void LineMesh::CreateMesh(ID3D12Device* device_)
{
	int const kNumVectorRequired = 2;
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer = static_cast<UINT>(sizeof(Vector3) * kNumVectorRequired);
	// 頂点バッファ生成
	vertexBuffer.Create(device_, sizeOfVertexBuffer);

	// 頂点バッファのマッピング
	HRESULT result = vertexBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));
	vertexBuffer.buffer->Unmap(0, nullptr);

	viewProjectionMatrixBuffer.matrix.CreateAndMapping(device_);

	for(auto& materialForLineBuffer : materialForLineBuffers)
	{
		materialForLineBuffer.material.CreateAndMapping(device_);
	}
}
void LineMesh::CreatePSO(AllPipelineSet* allPipelineset_)
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

				return descs;

		};

		auto rootparameterFunc = []() {

			std::vector<D3D12_ROOT_PARAMETER> meters;

			meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::VS, 0));
			meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 1));

			return meters;
			};

		std::string folderPath = "Line/";

		allPipelineset_->CreateNewPipeline(folderPath, "Line.VS", "Line.PS", inputLayOutFunc, rootparameterFunc);
	}

}

void LineMesh::DrawIndexReset()
{
	curDrawIndex = 0;
}

void LineMesh::DetectOverDrawing()
{
	assert(curDrawIndex < maxDraw);
}

UINT LineMesh::GetCurrentIndex()
{
	return curDrawIndex;
}

Vector3* LineMesh::GetVertexMap()
{
	return vertexMap;
}

void LineMesh::SetViewProjectionMatrix(Matrix4* src_)
{
	*viewProjectionMatrixBuffer.matrix.buffMap = *src_;
}

void LineMesh::SetMaterial(Vector4* color_, UINT index_)
{
	materialForLineBuffers[index_].material.buffMap->color = *color_;
}