#pragma once
#include <stdint.h>
#include <vector>
#include "../../../Buffer/VertexBuffer/VertexBuffer.h"
#include "../../../Buffer/constantBuffer/MatrixBuffer/MatrixBuffer.h"
#include "../../meshStructure/VertexForLine/VertexForLine.h"
#include "../../../Buffer/constantBuffer/MaterialBuffer/MaterialBuffer.h"


class AllPipelineSet;
struct ID3D12Device;

class LineMesh
{
private:

	enum MaxDraw
	{
		kLineMax = 1024 
	};

	uint16_t maxDraw;
	UINT curDrawIndex;
	VertexBuffer vertexBuffer;
	// マトリクスバッファ
	MatrixBuffer viewProjectionMatrixBuffer;
	// 頂点バッファマップ
	Vector3* vertexMap = nullptr;
	std::vector<MaterialForLineBuffer> materialForLineBuffers;

	void CreateMesh(ID3D12Device* device_);
	void Init(uint16_t maxDraw_ , AllPipelineSet* allPipelineset_);
	void CreatePSO(AllPipelineSet* allPipelineset_);

public:

	LineMesh(AllPipelineSet* allPipelineset_, ID3D12Device* device_);
	void DrawIndexReset();
	void DetectOverDrawing();
	UINT GetCurrentIndex();
	Vector3* GetVertexMap();
	void SetViewProjectionMatrix(Matrix4* src_);
	void SetMaterial(Vector4* color_,UINT index_);
	auto* GetVertexBufferView()
	{
		return &vertexBuffer.view;
	}

};

