#pragma once
#include <stdint.h>
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <assert.h>
#include <vector>

#include "../../meshStructure/Vertex/Vertex.h"
#include "../../../Buffer/constantBuffer/MatrixBuffer/MatrixBuffer.h"
#include "../../../Buffer/constantBuffer/MaterialBuffer/MaterialBuffer.h"
#include "../../../Buffer/VertexBuffer/VertexBuffer.h"
#include "../../../Buffer/IndexBuffer/IndexBuffer.h"

class AllPipelineSet;

struct MeshForPostEffect
{
	int const kMax = 10;

	// 頂点バッファマップ
	Vertex* vertexMap = nullptr;

protected:
	// 頂点バッファとそのびゅー
	VertexBuffer vertexBuffer;

public:

	MeshForPostEffect(ID3D12Device* device_, AllPipelineSet* allPipelineset_);

	auto* Getter_VertexBufferView()
	{
		return &vertexBuffer.view;
	}

private:
	void CreateMesh(ID3D12Device* device_);
	void CreatePSO(AllPipelineSet* allPipelineset_);

};
