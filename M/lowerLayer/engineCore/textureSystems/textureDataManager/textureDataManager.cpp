#include "textureDataManager.h"
#include "../../allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"


void TextureDataManager::Init(SrvDescriptorHeap* srvDescriptorHeap_, ID3D12Device* device_, CommandControl* commandControl_)
{
	textureDataCreator.Init(srvDescriptorHeap_, device_, commandControl_);

}

void TextureDataManager::CreateTextureFromFile(TextureTag tag_, std::string filePath_)
{
	map_textureID[tag_] = textureDataCreator.CreateShaderBufferFromFile(filePath_);
}