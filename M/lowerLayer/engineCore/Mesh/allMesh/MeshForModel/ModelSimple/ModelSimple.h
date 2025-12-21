#pragma once
#include "../MeshForModelCommon.h"

class ModelSimple :public MeshForModelCommon
{
public:
	virtual void CreateMesh(ID3D12Device* device_) override;
	ModelSimple(AllPipelineSet* allPipelineset_);

};

