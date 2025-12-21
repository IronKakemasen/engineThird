#pragma once
#include "../MeshForModelCommon.h"

class ModelSimple :public MeshAndDataCommon
{
public:
	virtual void CreateMesh(ID3D12Device* device_, int meshIndex_) override;
	ModelSimple(AllPipelineSet* allPipelineset_);

};

