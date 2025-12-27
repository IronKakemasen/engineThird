#pragma once
#include "../allMesh/MeshForModel/ModelSimple/ModelSimple.h"
#include <memory>

class TextureDataManager;
class CommandControl;
class FenceControl;
struct IDXGISwapChain4;

class MeshCreator
{
public:

	std::unique_ptr<ModelSimple> CreateModel(std::string filePath_);
	void Init(AllPipelineSet* allPipelineset_, ID3D12Device* device_, 
		TextureDataManager* textureDataManager_, CommandControl* commandControl_,
		FenceControl* fenceControl_, IDXGISwapChain4* swapChain_);

private:
	AllPipelineSet * allPipelineset = nullptr;
	ID3D12Device * device = nullptr;
	TextureDataManager* textureDataManager = nullptr;
	CommandControl* commandControl = nullptr;
	FenceControl* fenceControl = nullptr;
	IDXGISwapChain4* swapChain = nullptr;

	void InputTextureIndex(ModelSimple* model_, int index_, int textureHandleIndex_,
		std::string dirPath_, std::wstring textureFile_);
};

