#pragma once
#include <string>
#include <vector>
#include "../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../Buffer/PostEffectBuffer/PostEffectBuffer.h"

class TextureSrvCreator;
class PostEffectSrvCreator;

class TextureDataManager
{
	TextureSrvCreator* textureSrvCreator = nullptr;
	PostEffectSrvCreator* postEffectSrvCreator = nullptr;
	std::vector<ShaderBuffer> data;
	std::vector<PostEffectBuffer> postEffectBufferData;

public:

	void Init(TextureSrvCreator* textureSrvCreator_, PostEffectSrvCreator* postEffectSrvCreator_);
	int CreateTextureFromFile(std::string filePath_);
	PostEffectBuffer* CreatePostEffectBuffer();
};

