#pragma once
#include "./PostEffects/PostEffects.h"
#include "../Palette/Palette.h"

#include <unordered_map>
#include <memory>

class TextureDataManager;
class ExclusiveDraw;

class OffScreenManager
{
	PostEffectType* curOffscreen = nullptr;
	std::unique_ptr<OriginalScreen> originalScreen;
	ExclusiveDraw* exclusiveDraw = nullptr;
	TextureDataManager* textureDataManager = nullptr;
	std::unordered_map<PostEffectType, std::unique_ptr<OffScreen> >
		effectContainer;

	void SetEffectSysytem(PostEffectType type_, 
		std::unique_ptr<OffScreen> dst_);

	Palette palette;

public:
	inline OriginalScreen* GetOriginalScreen() { return originalScreen.get(); }
	inline Palette* GetPalette() { return &palette; }
	void Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_);
	void ChangePostEffection(PostEffectType type_);
};

