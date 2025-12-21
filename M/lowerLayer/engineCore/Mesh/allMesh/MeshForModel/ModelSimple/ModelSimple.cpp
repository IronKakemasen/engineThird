#include "ModelSimple.h"

void ModelSimple::CreateMesh(ID3D12Device* device_)
{
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer = static_cast<UINT>(sizeof(Vertex) * resMesh[0].vertices.size());
	// 頂点バッファ生成
	veretxBuffer.Create(device_, sizeOfVertexBuffer);

	// インデックスデータのサイズ
	UINT sizeOfIndexBuffer = static_cast<UINT>(sizeof(uint32_t) * resMesh[0].indices.size());
	// インデックスバッファ生成
	indexBuffer.Create(device_, sizeOfIndexBuffer);
	//頂点バッファのマッピング
	HRESULT result = veretxBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&resMesh[0].indices));
	assert(SUCCEEDED(result));

	// ワールド行列バッファ生成
	transformMatrixBuffer.matrix.CreateAndMapping(device_);
	// マテリアルバッファ作成
	materialBuffer.material.CreateAndMapping(device_);
}

ModelSimple::ModelSimple(AllPipelineSet* allPipelineset_)
{
	Init(allPipelineset_);
}
