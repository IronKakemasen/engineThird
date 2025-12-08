#include "quadMesh.h"

QuadMesh::QuadMesh(AllPipelineSet* allPipelineset_)
{
	Init((int)MaxDraw::kQuad, 4, 6, allPipelineset_);
}

void QuadMesh::CreateMesh(ID3D12Device* device_)
{
	// 頂点データのサイズ
	UINT sizeOfVertexBuffer = static_cast<UINT>(sizeof(VertexData) * vertexCnt);
	// 頂点バッファ生成
	vertexBuff = CreateBufferResource(device_, sizeOfVertexBuffer);

	// 頂点バッファビューの作成
	vertexBufferView.BufferLocation = vertexBuff->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeOfVertexBuffer;
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	// 頂点バッファのマッピング
	HRESULT result = vertexBuff->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));

	// インデックスデータのサイズ
	UINT sizeOfIndexBuffer = static_cast<UINT>(sizeof(uint32_t) * indexCnt);
	// インデックスバッファ生成
	indexBuff = CreateBufferResource(device_,sizeOfIndexBuffer);

	// インデックスバッファビューの作成
	indexBufferView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	indexBufferView.SizeInBytes = sizeOfIndexBuffer;

	// インデックスバッファのマッピング
	result = indexBuff->Map(0, nullptr, reinterpret_cast<void**>(&indexMap));
	assert(SUCCEEDED(result));


	for (UINT i = 0; i < kMaxDraw; ++i)
	{
		// 行列バッファ生成
		worldMatrixBuffer[i].matrix.CreateAndMapping(device_);
		//wvp行列バッファの生成
		wvpMatrixBuffer[i].matrix.CreateAndMapping(device_);
		// マテリアルバッファ作成
		materialBuffer[i].material.CreateAndMapping(device_);
	}

}


