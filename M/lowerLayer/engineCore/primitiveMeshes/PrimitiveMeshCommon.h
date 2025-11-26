#pragma once
#include <stdint.h>
#include <wrl.h>
#include <d3d12.h>
#include "../meshStructure/vertexData/VertexData.h"
#include "../meshStructure/vertexDataForLine/vertexDataForLine.h"
#include <memory>
#include <assert.h>
#include "../constantBuffer/MaterialBuffer/MaterialBuffer.h"
#include "../constantBuffer/MatrixBuffer/MatrixBuffer.h"
#include <vector>

class PipelineSet;

struct PrimitiveMeshCommon
{
	enum class MaxDraw
	{
		kTriangle = 128,
		kQuad = 128,
	};

	// 頂点バッファマップ
	VertexData* vertexMap = nullptr;
	// インデックスバッファマップ
	uint32_t* indexMap = nullptr;

	//マテリアルバッファ
	std::vector<MaterialBuffer> materialBuffer;
	//ワールドマトリクスバッファ
	std::vector<MatrixBuffer> worldMatrixBuffer;
	//WVPマトリクスバッファ
	std::vector<MatrixBuffer> wvpMatrixBuffer;

	uint16_t cur_drawIndex = 0;
	uint16_t kMaxDraw = 0;
	UINT vertexCnt = 0;
	UINT indexCnt = 0;

protected:
	virtual void Create(ID3D12Device* device_) = 0;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuff;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	void Init(uint16_t kMaxDraw_,UINT vertexCnt_,UINT indexCnt_);

public:

	void SetPipelineset(PipelineSet* pipelineSet_);
	void DrawIndexReset();
	void DetectOverDrawing();

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

