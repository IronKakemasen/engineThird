#include "Palette.h"
#include "../../../commonVariables.h"

Palette::Para::Para()
{
	shaderSetIndex = 0;
}

void Palette::Set(PostEffectType type_, std::vector<int> textures_,int shaderSetIndex_)
{
	para.offscreenTextureContainer[type_] = textures_;
	para.shaderSetIndex = shaderSetIndex_;
}

Palette::Palette()
{
	curType = PostEffectType::kNone;
}

int Palette::WatchShaderSetIndex()
{
	return para.shaderSetIndex;
}

std::vector<int> Palette::WatchUseTexture()
{
	return para.offscreenTextureContainer[curType];
}
