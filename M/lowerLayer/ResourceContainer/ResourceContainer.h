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

	kButtonBack200x60,
	kButtonDecision200x60,
	kButtonMove200x60,
	kButtonOption200x60,
	kButtonPause200x60,
	kButtonShot200x60,
	kButtonZoom200x60,
	kNumbers1000x100,
	kButtonReticle200x60,

	kStageName1000x100,

	kGroundN,

	kPlayerHeadN,
	kPlayerHandN,
	kPlayerLegN,
	kPlayerBodyN,
	kCannonN,

	kTowerN,
	kFactoryN,

	kBulletN,

	kScrewN,

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

