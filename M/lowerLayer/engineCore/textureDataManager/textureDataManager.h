#pragma once
#include <string>
#include <vector>
#include "../Buffer/gpuResources/Resource/shaderBuffer/shaderBuffer.h"

class TextureSrvCreator;

class TextureDataManager
{
	TextureSrvCreator* textureSrvCreator = nullptr;
	std::vector<ShaderBuffer> data;

public:

	void Init(TextureSrvCreator* textureSrvCreator_);
	int CreateTextureFromFile(std::string filePath_);

};

