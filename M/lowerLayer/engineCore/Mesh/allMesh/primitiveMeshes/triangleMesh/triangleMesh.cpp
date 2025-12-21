#include "triangleMesh.h"

TriangleMesh::TriangleMesh(AllPipelineSet* allPipelineset_)
{
	Init((int)MaxDraw::kTriangle, 3, 0, allPipelineset_);
}

void TriangleMesh::CreateMesh(ID3D12Device* device_)
{
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer = static_cast<UINT>(sizeof(Vertex) * vertexCnt);
	// 頂点バッファ生成
	veretxBuffer.Create(device_, sizeOfVertexBuffer);

	// 頂点バッファのマッピング
	HRESULT result = veretxBuffer.buffer->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));

	for (UINT i = 0; i < kMaxDraw; ++i)
	{
		// ワールド行列バッファ生成
		worldMatrixBuffer[i].matrix.CreateAndMapping(device_);
		//wvp行列バッファの生成
		wvpMatrixBuffer[i].matrix.CreateAndMapping(device_);
		// マテリアルバッファ作成
		materialBuffer[i].material.CreateAndMapping(device_);
	}

}
