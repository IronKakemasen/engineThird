#pragma once
#include <stdint.h>
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <assert.h>
#include <vector>

#include "../../../Buffer/constantBuffer/TransformMatrixBuffer/TransformMatrixBuffer.h"
#include "../../../Buffer/constantBuffer/MaterialBuffer/MaterialBuffer.h"

class AllPipelineSet;



struct MeshForModelCommon
{
	//マテリアルバッファ
	MaterialBuffer materialBuffer;
	//World,WVP
	TransformMatrixBuffer transformMatrixBuffer;

protected:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuff;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	virtual void CreateMesh(ID3D12Device* device_) = 0;
	void Init(AllPipelineSet* allPipelineset_);

public:

	auto* Getter_VertexBufferView()
	{
		return &vertexBufferView;
	}

	auto* Getter_IndexBufferView()
	{
		return &indexBufferView;
	}

	auto* IndexBufferView()
	{
		return &indexBufferView;
	}

private:

	void CreatePSO(AllPipelineSet* allPipelineset_);

};

