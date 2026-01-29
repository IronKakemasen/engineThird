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

	LoadTextureFile(TextureTag::kButtonBack900x250, pathToUI + "ButtonBack900x250.png");
	LoadTextureFile(TextureTag::kButtonDecision900x250, pathToUI + "ButtonDecision900x250.png");
	LoadTextureFile(TextureTag::kButtonMove900x250, pathToUI + "ButtonMove900x250.png");
	LoadTextureFile(TextureTag::kButtonOption900x250, pathToUI + "ButtonOption900x250.png");
	LoadTextureFile(TextureTag::kButtonPause900x250, pathToUI + "ButtonPause900x250.png");
	LoadTextureFile(TextureTag::kButtonShot900x250, pathToUI + "ButtonShot900x250.png");
	LoadTextureFile(TextureTag::kButtonZoom900x250, pathToUI + "ButtonZoom900x250.png");
	LoadTextureFile(TextureTag::kNumbers100x100, pathToUI + "Numbers100x100.png");
	LoadTextureFile(TextureTag::kButtonReticle900x250, pathToUI + "ButtonReticle900x250.png");
	LoadTextureFile(TextureTag::kGroundN, pathToTex + "Ground/"  + "Ground_normal.png");

	LoadTextureFile(TextureTag::kPlayerHeadN, pathToPlayer + "P_Head_normal.png");
	LoadTextureFile(TextureTag::kPlayerHandN, pathToPlayer + "P_Hand_normal.png");
	LoadTextureFile(TextureTag::kPlayerBodyN, pathToPlayer + "P_Body_normal.png");
	LoadTextureFile(TextureTag::kPlayerLegN, pathToPlayer +  "P_Leg_normal.png");

	LoadTextureFile(TextureTag::kTowerN, pathToTower + "Tower_normal.png");
	LoadTextureFile(TextureTag::kFactoryN, pathToFactory + "Factory_normal.png");


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