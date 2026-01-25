#include "OffScreenManager.h"
#include "../engineCore/textureDataManager/textureDataManager.h"


void OffScreenManager::Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_)
{
	textureDataManager = textureDataManager_;
	exclusiveDraw = exclusiveDraw_;

	originalScreen.reset(new OriginalScreen(textureDataManager_, 1));
	originalScreen->Init();

	palette.Init(originalScreen.get());

	SetEffectSysytem(PostEffectType::kNone,
		std::make_unique<PostEffects::NoEffection>(textureDataManager_, 0));
	SetEffectSysytem(PostEffectType::kBloom, 
		std::make_unique<PostEffects::Bloom>(textureDataManager_,3));
	SetEffectSysytem(PostEffectType::kGreyScale,
		std::make_unique<PostEffects::GreyScale>(textureDataManager_, 0));

	for (int i = 0; i < (int)PostEffectType::kCount; ++i)
	{
		auto* it = effectContainer[PostEffectType(i)].get();

		it->Init();

		palette.Set(PostEffectType(i),
			it->WatchTextureIndexes(), it->WathchShaderSetIndex());
	}

	ChangePostEffection(PostEffectType::kGreyScale);
}

void OffScreenManager::SetEffectSysytem(PostEffectType type_,
	std::unique_ptr<OffScreen> dst_)
{
	effectContainer[type_] = std::move(dst_);
}

void OffScreenManager::ChangePostEffection(PostEffectType type_)
{
	palette.ChangeType(type_);
}
