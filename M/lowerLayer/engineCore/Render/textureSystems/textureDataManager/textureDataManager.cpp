#include "textureDataManager.h"
#include "../../../DescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../../../Buffer/gpuResources/Creator/SrvCreator/TextureSrvCreator/TextureSrvCreator.h"


void TextureDataManager::Init(TextureSrvCreator* textureSrvCreator_)
{
	textureSrvCreator = textureSrvCreator_;
}

int TextureDataManager::CreateTextureFromFile( std::string filePath_)
{
	return textureSrvCreator->CreateShaderBufferFromFile(filePath_);
}