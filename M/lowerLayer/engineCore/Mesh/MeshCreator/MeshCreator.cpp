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

		//texMapのインデックスの読み込み
		std::filesystem::path fullPath = filePath_;
		std::filesystem::path dirPath = fullPath.parent_path();
		std::string cnv = dirPath.string() + "/";

		//カラーマップ
		InputTextureIndex(model.get(), i, Appearance::kColormap,
			cnv, model->Getter_ModelData().resMaterial[i].colorMap);

		//法線マップ
		InputTextureIndex(model.get(), i, Appearance::kNormalmap,
			cnv, model->Getter_ModelData().resMaterial[i].normalMap);

		//スペキュラーマップ
		InputTextureIndex(model.get(), i, Appearance::kSpecularMap,
			cnv, model->Getter_ModelData().resMaterial[i].specularMap);

		//シャインネスマップ
		InputTextureIndex(model.get(), i, Appearance::kShininessMap,
			cnv, model->Getter_ModelData().resMaterial[i].shininessMap);
	}

	commandControl->Getter_commandList()->Close();
	ID3D12CommandList* commandLists[] = { commandControl->Getter_commandList() };
	commandControl->Getter_CommandQueue()->ExecuteCommandLists(1, commandLists);
	fenceControl->WaitFenceEvent(commandControl->Getter_CommandQueue(), swapChain);

	return std::move(model);
}

void MeshCreator::InputTextureIndex(ModelSimple* model_,int index_,
	Appearance::TextureType textureHandleIndex_,
	std::string dirPath_,std::wstring textureFile_)
{
	if (textureFile_.empty())
	{
		return;
	}

	//colorMapのインデックスの読み込み
	std::string texMapFilePath = dirPath_ + ConvertString(textureFile_);
	(*model_->Getter_Appearance())[index_].texHandlesContainer[textureHandleIndex_] =
		textureDataManager->CreateTextureFromFile(texMapFilePath);

}
