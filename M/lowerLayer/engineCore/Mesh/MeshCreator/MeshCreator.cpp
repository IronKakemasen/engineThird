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
	model = std::make_unique<ModelSimple>(allPipelineset);

	std::wstring converted_filePath = ConvertString(filePath_);
	const wchar_t* tmp  = converted_filePath.c_str();
	assert(LoadMesh(tmp, model->Getter_ModelData().resMesh, 
		model->Getter_ModelData().resMaterial));
	
	int size = (int)model->Getter_ModelData().resMesh.size();
	model->ResizeMeshSize(size);

	for (int i = 0; i < size; ++i)
	{
		model->CreateMesh(device,i);
	}

	return std::move(model);
}
