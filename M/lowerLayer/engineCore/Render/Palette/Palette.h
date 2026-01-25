#pragma once
#include "PostEffectType.h"
#include "../../utilities/vectorAndMatrix/vectorAndMatrix.h"
#include <unordered_map>

class OriginalScreen;
class Palette
{
	class Para
	{

	public:

		int shaderSetIndex;
		std::vector<uint16_t> offscreenTextureContainer;

		Para();
	};

	PostEffectType curType;
	std::unordered_map < PostEffectType, Para> paraContainer;
	OriginalScreen* originalScreen = nullptr;
public:
	void Init(OriginalScreen* originalScreen_);
	Palette();
	int WatchShaderSetIndex();
	std::vector<uint16_t> WatchUseTexture();
	void Set(PostEffectType type_, std::vector<uint16_t> textures_, int shaderSetIndex_);
	void ChangeType(PostEffectType type_);
};

