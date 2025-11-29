#include "TestParticleMesh.h"
#include "../../../../Model/MobilePrimitive/MobileQuad/MQuad/MQuad.h"
#include "../../../Buffer/gpuResources/Creator/SrvCreator/ParticleMeshSrvCreator/ParticleMeshSrvCreator.h"


void TestParticleMesh::Create(ID3D12Device* device_, ParticleMeshSrvCreator* particleMeshSrvCreator_)
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
	MQuad mQuad;
	mQuad.SetVertex(width, height);
	mQuad.SetNormal();
	mQuad.SetTexcoord();

	VertexData vData[4] =
	{
		mQuad.leftTop,	mQuad.rightTop,mQuad.rightBottom,mQuad.leftBottom
	};

	HRESULT result = vertexBuff->Map(0, nullptr, reinterpret_cast<void**>(&vertexMap));
	assert(SUCCEEDED(result));
	std::memcpy(&vertexMap[0], vData, sizeof(VertexData) * vertexCnt);
	//vertexBuff->Unmap();

	// インデックスデータのサイズ
	UINT sizeOfIndexBuffer = static_cast<UINT>(sizeof(uint32_t) * indexCnt);
	// インデックスバッファ生成
	indexBuff = CreateBufferResource(device_,sizeOfIndexBuffer);

	// インデックスバッファビューの作成
	indexBufferView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	indexBufferView.SizeInBytes = sizeOfIndexBuffer;

	// インデックスバッファのマッピング
	uint32_t indices[6] = { 0,1,2,2,1,3 };
	result = indexBuff->Map(0, nullptr, reinterpret_cast<void**>(&indexMap));
	assert(SUCCEEDED(result));
	std::memcpy(&indexMap[0], indices, sizeof(uint32_t) * indexCnt);
	//indexBuff->Unmap();

	// 行列バッファ生成
	transformMatrixStructuredBuffer.matrix.CreateAndMapping(device_, (UINT)kMaxDraw);

	// マテリアルバッファ作成
	materialBuffer.material.CreateAndMapping(device_);

	//SRVの作成
	srvIndex = particleMeshSrvCreator_->CreateSRVForParticle(kMaxDraw,
		transformMatrixStructuredBuffer.matrix.shaderBuffer);

}

TestParticleMesh::TestParticleMesh()
{
	Init(10, 32, 32);
}
