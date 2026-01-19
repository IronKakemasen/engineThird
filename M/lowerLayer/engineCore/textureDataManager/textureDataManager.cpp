#include "textureDataManager.h"
#include "../DescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../Buffer/gpuResources/Creator/SrvCreator/TextureSrvCreator/TextureSrvCreator.h"
#include "../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../Buffer/gpuResources/Creator/SrvCreator/PostEffectSrvCreator/PostEffectSrvCreator.h"

void TextureDataManager::Init(TextureSrvCreator* textureSrvCreator_, PostEffectSrvCreator* postEffectSrvCreator_)
{
	textureSrvCreator = textureSrvCreator_;
	postEffectSrvCreator = postEffectSrvCreator_;
}

int TextureDataManager::CreateTextureFromFile( std::string filePath_)
{
	auto& dst = data.emplace_back();
	return textureSrvCreator->CreateShaderBufferFromFile(filePath_, dst);
}

PostEffectBuffer* TextureDataManager::CreatePostEffectBuffer()
{
	auto* dst = &postEffectBufferData.emplace_back();	
	*dst->GetSrvHandle() = postEffectSrvCreator->CreateSRVForPostEffect(dst);

	return dst;
}