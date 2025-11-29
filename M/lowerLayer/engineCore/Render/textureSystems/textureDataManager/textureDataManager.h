#pragma once
#include <string>
#include <vector>

struct SrvDescriptorHeap;
class CommandControl;
class TextureSrvCreator;
struct ShaderBuffer;

class TextureDataManager
{
	TextureSrvCreator* textureSrvCreator = nullptr;
\
public:

	void Init(TextureSrvCreator* textureSrvCreator_);
	int CreateTextureFromFile(std::string filePath_);

};

