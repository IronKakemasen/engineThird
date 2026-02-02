#include "ResourceContainer.h"
#include "../engineCore/textureDataManager/textureDataManager.h"
#include "../engineCore/WinApp.h"

void ResourceContainer::LoadAllTextureFile()
{
	std::string pathToPresetTex = "./resource/preset/texture/";
	std::string pathToTex = "./resource/application/Texture/";
	std::string pathToUI = "./resource/application/Texture/UI/";
	std::string pathToPlayer = "./resource/application/Texture/Player/";
	std::string pathToTower = "./resource/application/Texture/Tower/";
	std::string pathToFactory = "./resource/application/Texture/Factory/";
	std::string pathToBullet = "./resource/application/Texture/Bullet/";
	std::string pathToGround = "./resource/application/Texture/Ground/";

	LoadTextureFile(TextureTag::kWhite2x2, pathToPresetTex + "white2x2.png");
	LoadTextureFile(TextureTag::kSouhei, pathToPresetTex + "nNani.png");
	LoadTextureFile(TextureTag::kPlayer, pathToPresetTex + "player128x128.png");
	LoadTextureFile(TextureTag::kNothing, pathToPresetTex + "header.jpg");
	LoadTextureFile(TextureTag::kGridN, pathToPresetTex + "gridLineNormal.png");
	LoadTextureFile(TextureTag::kAtlasNumbers, pathToPresetTex + "numbers48x48.png");
	LoadTextureFile(TextureTag::kOh, pathToPresetTex + "oh.png");
	LoadTextureFile(TextureTag::kCursorImage, pathToPresetTex + "cursorImage.png");
	LoadTextureFile(TextureTag::kNormalDekoboko, pathToPresetTex + "dekoboko.png");
	LoadTextureFile(TextureTag::kEnemyN, pathToTex + "EnemyN.png");
	LoadTextureFile(TextureTag::kEnemyBodyN, pathToTex + "Enemy/" +"E_Body_normal.png");
	LoadTextureFile(TextureTag::kEnemyThornN, pathToTex + "Enemy/" + "E_Thorn_normal.png");
	LoadTextureFile(TextureTag::kAllyN, pathToTex + "Ally/" + "Ally_Body_normal.png");

	LoadTextureFile(TextureTag::kButtonBack200x60, pathToUI + "Common/" + "ButtonBack200x60.png");
	LoadTextureFile(TextureTag::kButtonDecision200x60, pathToUI + "Common/" + "ButtonDecision200x60.png");
	LoadTextureFile(TextureTag::kButtonMove200x60, pathToUI + "Common/" + "ButtonMove200x60.png");
	LoadTextureFile(TextureTag::kButtonOption200x60, pathToUI + "Common/" + "ButtonOption200x60.png");
	LoadTextureFile(TextureTag::kButtonPause200x60, pathToUI + "Common/" + "ButtonPause200x60.png");
	LoadTextureFile(TextureTag::kButtonShot200x60, pathToUI + "Common/" + "ButtonShot200x60.png");
	LoadTextureFile(TextureTag::kButtonZoom200x60, pathToUI + "Common/" + "ButtonZoom200x60.png");
	LoadTextureFile(TextureTag::kNumbers1000x100, pathToUI + "Common/" + "Numbers1000x100.png");
	LoadTextureFile(TextureTag::kButtonReticle200x60, pathToUI + "Common/" + "ButtonReticle200x60.png");
	LoadTextureFile(TextureTag::kGroundN, pathToTex + "Ground/"  + "Ground_normal.png");

	LoadTextureFile(TextureTag::kPlayerHeadN, pathToPlayer + "P_Head_normal.png");
	LoadTextureFile(TextureTag::kPlayerHandN, pathToPlayer + "P_Hand_normal.png");
	LoadTextureFile(TextureTag::kPlayerBodyN, pathToPlayer + "P_Body_normal.png");
	LoadTextureFile(TextureTag::kPlayerLegN, pathToPlayer +  "P_Leg_normal.png");
	LoadTextureFile(TextureTag::kCannonN, pathToPlayer + "Cannon_normal.png");

	
	LoadTextureFile(TextureTag::kTowerN, pathToTower + "Tower_normal.png");
	LoadTextureFile(TextureTag::kFactoryN, pathToFactory + "Factory_normal.png");

	LoadTextureFile(TextureTag::kBulletN, pathToBullet + "PlayerBullet_normal.png");

	LoadTextureFile(TextureTag::kGroundN, pathToGround + "Ground_normal.png");

	LoadTextureFile(TextureTag::kScrewN, pathToFactory + "screw_normal.png");

	
}

int ResourceContainer::GetTextureIndex(TextureTag tag_)
{
	return map_textureID[tag_];
}

void ResourceContainer::Init(TextureDataManager* textureManager_)
{
	static bool onlyOnce = true;
	if (onlyOnce)
	{
		textureManager = textureManager_;
		LoadAllTextureFile();
		Log(WinApp::log, "Complete : LoadTexture");

		onlyOnce = false;
	}

}

void ResourceContainer::LoadTextureFile(TextureTag tag_, std::string filePath_)
{
	map_textureID[tag_] = textureManager->CreateTextureFromFile(filePath_);
}