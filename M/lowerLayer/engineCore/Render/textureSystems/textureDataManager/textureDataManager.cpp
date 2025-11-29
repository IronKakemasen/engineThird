#include "textureDataManager.h"
#include "../../../DescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../../../Buffer/gpuResources/Creator/SrvCreator/TextureSrvCreator/TextureSrvCreator.h"
#include "../../../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"

void TextureDataManager::Init(TextureSrvCreator* textureSrvCreator_)
{
	textureSrvCreator = textureSrvCreator_;
}

int TextureDataManager::CreateTextureFromFile( std::string filePath_)
{
	auto& dst = data.emplace_back();
	return textureSrvCreator->CreateShaderBufferFromFile(filePath_, dst);
}