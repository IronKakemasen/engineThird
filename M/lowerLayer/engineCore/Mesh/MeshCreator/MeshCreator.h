#pragma once
#include "../allMesh/MeshForModel/ModelSimple/ModelSimple.h"
#include <memory>


class MeshCreator
{
public:

	std::unique_ptr<ModelSimple> CreateModel(std::string filePath_);
	void Init(AllPipelineSet* allPipelineset_, ID3D12Device* device_);

private:
	AllPipelineSet * allPipelineset = nullptr;
	ID3D12Device * device = nullptr;
};

