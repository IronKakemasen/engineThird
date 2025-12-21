#pragma once
#include <stdint.h>
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include <assert.h>
#include <vector>

#include "../../../Buffer/constantBuffer/TransformMatrixBuffer/TransformMatrixBuffer.h"
#include "../../../Buffer/constantBuffer/MaterialBuffer/MaterialBuffer.h"
#include "../../../Buffer/VertexBuffer/VertexBuffer.h"
#include "../../../Buffer/IndexBuffer/IndexBuffer.h"
#include "../../meshStructure/ModelData/ModelData.h"

class AllPipelineSet;

struct MeshForModelCommon
{
	//マテリアルバッファ
	MaterialBuffer materialBuffer;
	//World,WVP
	TransformMatrixBuffer transformMatrixBuffer;
	std::vector<ResMaterial> resMaterial;
	std::vector<ResMesh> resMesh;

protected:
	// 頂点バッファとそのびゅー
	VertexBuffer veretxBuffer;
	// インデックスバッファとそのびゅー
	IndexBuffer indexBuffer;

	virtual void CreateMesh(ID3D12Device* device_) = 0;
	void Init(AllPipelineSet* allPipelineset_);

public:

	auto* Getter_VertexBufferView()
	{
		return &veretxBuffer.view;
	}

	auto* Getter_IndexBufferView()
	{
		return &indexBuffer.view;
	}


private:

	void CreatePSO(AllPipelineSet* allPipelineset_);

};

