#include "MeshCreator.h"
#include "./MeshLoader/MeshLoader.h"
#include "../../../../utilities/convertString/convertString.h"
#include <assert.h>
#include "../meshStructure/ModelData/ModelData.h"


void MeshCreator::Init(AllPipelineSet* allPipelineset_, ID3D12Device* device_)
{
	allPipelineset = allPipelineset_;
	device = device_;
}

std::unique_ptr<ModelSimple> MeshCreator::CreateModel(std::string filePath_)
{
	std::unique_ptr<ModelSimple> model;
	model.reset(new ModelSimple(allPipelineset));

	std::wstring converted_filePath = ConvertString(filePath_);
	assert(LoadMesh((wchar_t*)(&converted_filePath), model->resMesh, model->resMaterial));

	model->CreateMesh(device);

	return std::move(model);
}
