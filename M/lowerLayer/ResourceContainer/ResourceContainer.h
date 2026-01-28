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
	kEnemyBodyN,
	kEnemyThornN,
	kAllyN,

	kButtonBack900x250,
	kButtonDecision900x250,
	kButtonMove900x250,
	kButtonOption900x250,
	kButtonPause900x250,
	kButtonShot900x250,
	kButtonZoom900x250,
	kNumbers100x100,

	kStageName1000x100,

	kGroundN,

	kPlayerHeadN,
	kPlayerHandN,
	kPlayerLegN,
	kPlayerBodyN,

	kTowerN,
	kFactoryN,

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

