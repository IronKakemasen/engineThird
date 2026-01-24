#pragma once
#include "PostEffectType.h"
#include "../../utilities/vectorAndMatrix/vectorAndMatrix.h"
#include <unordered_map>

class Palette
{
	class Para
	{

	public:

		int shaderSetIndex;
		std::unordered_map < PostEffectType, std::vector<int>>
			offscreenTextureContainer;

		Para();

	};

	Para para;
	PostEffectType curType;

public:
	Palette();
	int WatchShaderSetIndex();
	std::vector<int> WatchUseTexture();
	void Set(PostEffectType type_, std::vector<int> textures_, int shaderSetIndex_);
};

