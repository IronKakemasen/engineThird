#pragma once
#include <stdint.h>
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <assert.h>
#include <vector>
#include "../meshStructure/vertexData/VertexData.h"
#include "../meshStructure/vertexDataForLine/vertexDataForLine.h"
#include "../constantBuffer/MaterialBuffer/MaterialBuffer.h"
#include "../constantBuffer/TransformMatrixBuffer/TransformMatrixBuffer.h"

class ParticleMeshSrvCreator;

struct ParticleMesh2DCommon
{
	//マテリアルバッファ
	MaterialBuffer materialBuffer;
	//WVPワールドマトリクスバッファ
	TransformMatrixBuffer transformMatrixBuffer;

	uint16_t kMaxDraw = 0;
	UINT vertexCnt = 0;
	UINT indexCnt = 0;
	float width;
	float height;
	//srvのインデックス
	uint16_t srvIndex;

protected:

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuff;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	// 頂点バッファマップ
	VertexData* vertexMap = nullptr;
	// インデックスバッファマップ
	uint32_t* indexMap = nullptr;

	virtual void Create(ID3D12Device* device_, ParticleMeshSrvCreator* ParticleMeshSrvCreator_) = 0;
	void Init(uint16_t kMaxDraw_, float width_, float height_);

public:

	ParticleMesh2DCommon();

	void DetectOverDrawing(int sum_draw_);

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

};
