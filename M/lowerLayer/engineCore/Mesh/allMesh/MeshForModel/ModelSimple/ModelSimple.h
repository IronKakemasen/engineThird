#pragma once
#include "../MeshForModelCommon.h"
#include "../../../../Render/Appearance/Appearance.h"

class ModelSimple :public MeshAndDataCommon
{
	Appearance appearance;

public:
	virtual void CreateMesh(ID3D12Device* device_, int meshIndex_) override;
	ModelSimple(AllPipelineSet* allPipelineset_);

};

