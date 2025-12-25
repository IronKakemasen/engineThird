#include "MeshCreator.h"
#include "./MeshLoader/MeshLoader.h"
#include "../../../../utilities/convertString/convertString.h"
#include "../meshStructure/ModelData/ModelData.h"
#include "../../textureDataManager/textureDataManager.h"
#include "../../Essential/CommandControl/CommandControl.h"
#include "../../Essential/FenceControl/FenceControl.h"
#include "../../../M.h"

#include <filesystem>
#include <assert.h>

void MeshCreator::Init(AllPipelineSet* allPipelineset_, ID3D12Device* device_, 
	TextureDataManager* textureDataManager_, CommandControl* commandControl_,
	FenceControl* fenceControl_, IDXGISwapChain4* swapChain_)
{
	allPipelineset = allPipelineset_;
	device = device_;
	textureDataManager = textureDataManager_;
	commandControl = commandControl_;
	fenceControl = fenceControl_;
	swapChain = swapChain_;
}

std::unique_ptr<ModelSimple> MeshCreator::CreateModel(std::string filePath_)
{
	std::unique_ptr<ModelSimple> model;
	model = std::make_unique<ModelSimple>(allPipelineset);

	//ファイルからメッシュと、マテリアルデータを読み込む
	std::wstring converted_filePath = ConvertString(filePath_);
	const wchar_t* tmp  = converted_filePath.c_str();
	assert(LoadMesh(tmp, model->Getter_ModelData().resMesh, 
		model->Getter_ModelData().resMaterial));
	
	//モデルの個数分拡張する
	int size = (int)model->Getter_ModelData().resMesh.size();
	model->ResizeMeshSize(size);

	// コマンドの記録を開始.
	commandControl->PrepareForNextCommandList();

	for (int i = 0; i < size; ++i)
	{
		//メッシュの生成
		model->CreateMesh(device,i);

		//diffuseMapのインデックスの読み込み
		std::filesystem::path fullPath = filePath_;
		std::filesystem::path dirPath = fullPath.parent_path();
		std::string cnv = dirPath.string() + "/";
		std::string diffuseMapFilePath = cnv + ConvertString(
			model->Getter_ModelData().resMaterial[i].diffuseMap);
		model->Getter_ModelData().appearance[i].texHandle =
			textureDataManager->CreateTextureFromFile(diffuseMapFilePath);

		//shaderSetの初期化
		model->Getter_ModelData().appearance[i].shaderSetIndex = 
			M::GetInstance()->
			GetShaderSetIndexFromFileName("ModelSimple.VS", "ModelSimple.PS");
	}

	commandControl->Getter_commandList()->Close();
	ID3D12CommandList* commandLists[] = { commandControl->Getter_commandList() };
	commandControl->Getter_CommandQueue()->ExecuteCommandLists(1, commandLists);
	fenceControl->WaitFenceEvent(commandControl->Getter_CommandQueue(), swapChain);

	return std::move(model);
}
