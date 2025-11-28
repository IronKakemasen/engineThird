#pragma once
#include <string>

struct SrvDescriptorHeap;
class CommandControl;
class TextureSrvCreator;

class TextureDataManager
{
	TextureSrvCreator* textureSrvCreator = nullptr;;

public:

	void Init(TextureSrvCreator* textureSrvCreator_);
	int CreateTextureFromFile(std::string filePath_);

};

