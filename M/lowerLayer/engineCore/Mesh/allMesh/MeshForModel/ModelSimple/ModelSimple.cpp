#include "ModelSimple.h"

void ModelSimple::CreateMesh(ID3D12Device* device_,int meshIndex_)
{
	auto* resMeshes = Getter_ModelDataOfResMeshes(meshIndex_);
	auto* resMaterials = Getter_ModelDataOfResMaterials(meshIndex_);
	auto* meshForModel = Getter_MeshForModel(meshIndex_);

	// 頂点データのサイズ
	UINT sizeOfVertexBuffer =
		static_cast<UINT>(sizeof(Vertex) * resMeshes->vertices.size());
	// 頂点バッファ生成
	meshForModel->veretxBuffer.Create(device_, sizeOfVertexBuffer);
	//頂点バッファのマッピング
	HRESULT result = meshForModel->veretxBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&meshForModel->vertexMap));
	assert(SUCCEEDED(result));
	//頂点データの入力
	std::memcpy(meshForModel->vertexMap, resMeshes->vertices.data(),
		sizeof(Vertex) * resMeshes->vertices.size());


	// インデックスデータのサイズ
	UINT sizeOfIndexBuffer = static_cast<UINT>(sizeof(uint32_t) * resMeshes->indices.size());
	// インデックスバッファ生成
	meshForModel->indexBuffer.Create(device_, sizeOfIndexBuffer);
	//インデックスバッファのマッピング
	result = meshForModel->indexBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&meshForModel->indexMap));
	assert(SUCCEEDED(result));
	//インデックスデータの入力
	std::memcpy(meshForModel->indexMap, resMeshes->indices.data(),
		sizeof(uint32_t) * resMeshes->indices.size());

	// ワールド行列バッファ生成
	meshForModel->transformMatrixBuffer.matrix.CreateAndMapping(device_);
	// マテリアルバッファ作成
	meshForModel->materialBuffer.material.CreateAndMapping(device_);
}

ModelSimple::ModelSimple(AllPipelineSet* allPipelineset_)
{
	Init(allPipelineset_);
}
