#include "ResourceContainer.h"
#include "../engineCore/textureDataManager/textureDataManager.h"
#include "../engineCore/WinApp.h"

void ResourceContainer::LoadAllTextureFile()
{
	std::string pathToPresetTex = "./resource/preset/texture/";
	std::string pathToTex = "./resource/application/Texture/";
	std::string pathToUI = "./resource/application/Texture/UI/";

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