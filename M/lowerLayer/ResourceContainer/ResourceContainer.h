#pragma once
#include <unordered_map>
#include <string>


class TextureDataManager;

enum class TextureTag
{
	kWhite2x2,
	kSouhei,
	kPlayer,
	kNothing,
	kGridN,
	kAtlasNumbers,
	kOh,
	kCursorImage,
	kNormalDekoboko,
	kEnemyN,

	kCount
};

class ResourceContainer
{
	std::unordered_map<TextureTag, int> map_textureID;
	void LoadTextureFile(TextureTag tag_, std::string filePath_);
	void LoadAllTextureFile();
	TextureDataManager* textureManager = nullptr;

public:

	void Init(TextureDataManager* textureManager_);
	int GetTextureIndex(TextureTag tag_);

};

