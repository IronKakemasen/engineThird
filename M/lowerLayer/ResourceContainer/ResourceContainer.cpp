#include "ResourceContainer.h"
#include "../engineCore/textureSystems/textureDataManager/textureDataManager.h"
#include "../engineCore/WinApp.h"

void ResourceContainer::LoadAllTextureFile()
{
	std::string 	pathToPresetTex =   "./M/resource/preset/texture/";

	LoadTextureFile(TextureTag::kWhite2x2, pathToPresetTex + "white2x2.png");


}

int ResourceContainer::GetTextureIndex(TextureTag tag_)
{
	return map_textureID[tag_];
}

void ResourceContainer::Init(TextureDataManager* textureManager_)
{
	textureManager = textureManager_;
	LoadAllTextureFile();
	Log(WinApp::log, "Complete : LoadTexture");

}

void ResourceContainer::LoadTextureFile(TextureTag tag_, std::string filePath_)
{
	map_textureID[tag_] = textureManager->CreateTextureFromFile(filePath_);
}