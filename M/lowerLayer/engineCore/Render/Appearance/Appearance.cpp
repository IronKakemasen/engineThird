#include "Appearance.h"

Appearance::Appearance()
{
	color = { 255,255,255,255 };
	cullMode = kCullModeBack;
	blendMode = kBlendModeNormal;
	shaderSetIndex = 0;
	doDraw = true;
	use_texHandles.resize(1);
	use_texHandles[0] = 0;		//(White2x2)
	texHandlesContainer[kColormap] = 0;		//(White2x2)
}

void Appearance::SetUsingTextureFromContainer(TextureType colorMap_, TextureType normalMap_)
{
	use_texHandles.clear();

	if (colorMap_ != kNone)
	{
		use_texHandles.emplace_back(texHandlesContainer[colorMap_]);
	}

	if (normalMap_ != kNone)
	{
		use_texHandles.emplace_back(texHandlesContainer[normalMap_]);
	}

}



