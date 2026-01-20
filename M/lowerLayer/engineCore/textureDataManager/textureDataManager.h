#pragma once
#include <string>
#include <vector>
#include "../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../Buffer/PostEffectBuffer/PostEffectBuffer.h"

class TextureSrCreator;
class PostEffectSrCreator;

class TextureDataManager
{
	TextureSrCreator* textureSrvCreator = nullptr;
	PostEffectSrCreator* postEffectSrCreator = nullptr;
	std::vector<ShaderBuffer> data;
	std::vector<std::unique_ptr<PostEffectBuffer>> postEffectBufferContaier;

public:

	void Init(TextureSrCreator* textureSrvCreator_, PostEffectSrCreator* postEffectSrCreator_);
	int CreateTextureFromFile(std::string filePath_);
	PostEffectBuffer* CreatePostEffectBuffer();
};

