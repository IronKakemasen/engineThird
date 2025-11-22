#include "textureDataManager.h"
#include "../../allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"


void TextureDataManager::Init(SrvDescriptorHeap* srvDescriptorHeap_, ID3D12Device* device_, CommandControl* commandControl_)
{
	textureDataCreator.Init(srvDescriptorHeap_, device_, commandControl_);

}

int TextureDataManager::CreateTextureFromFile( std::string filePath_)
{
	return textureDataCreator.CreateShaderBufferFromFile(filePath_);
}