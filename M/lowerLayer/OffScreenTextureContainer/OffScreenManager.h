#pragma once
#include "./PostEffects/PostEffects.h"
#include <unordered_map>
#include <memory>
#include "../engineCore/Render/Palette/PostEffectType.h"

class TextureDataManager;

class OffScreenManager
{
	TextureDataManager* textureDataManager = nullptr;
	std::unordered_map<PostEffectType, std::unique_ptr<PostEffects::PostEffect> >
		effectContainer;

	void SetEffectSysytem(PostEffectType type_, 
		std::unique_ptr<PostEffects::PostEffect> dst_);

public:
	void Init(TextureDataManager* textureDataManager_);
};

