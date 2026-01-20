#include "textureDataManager.h"
#include "../DescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../Buffer/gpuResources/Creator/SrvCreator/TextureSrCreator/TextureSrCreator.h"
#include "../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../Buffer/gpuResources/Creator/SrvCreator/PostEffectSrCreator/PostEffectSrCreator.h"

void TextureDataManager::Init(TextureSrCreator* textureSrvCreator_, PostEffectSrCreator* postEffectSrCreator_)
{
	textureSrvCreator = textureSrvCreator_;
	postEffectSrCreator = postEffectSrCreator_;
}

int TextureDataManager::CreateTextureFromFile( std::string filePath_)
{
	auto& dst = data.emplace_back();
	return textureSrvCreator->CreateShaderBufferFromFile(filePath_, dst);
}

PostEffectBuffer* TextureDataManager::CreatePostEffectBuffer()
{
	postEffectBufferContaier.emplace_back(postEffectSrCreator->Create());

	return postEffectBufferContaier.emplace_back(postEffectSrCreator->Create()).get();
}