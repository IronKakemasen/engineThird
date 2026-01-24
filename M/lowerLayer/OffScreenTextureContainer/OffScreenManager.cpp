#include "OffScreenManager.h"
#include "../engineCore/textureDataManager/textureDataManager.h"


void OffScreenManager::Init(TextureDataManager* textureDataManager_)
{
	textureDataManager = textureDataManager_;

	SetEffectSysytem(PostEffectType::kBloom, std::make_unique<PostEffects::Bloom>());
	SetEffectSysytem(PostEffectType::kNone, std::make_unique<PostEffects::NoEffection>());

	for (auto& effect : effectContainer)
	{
		effect.second->Init(textureDataManager_);
	}

}

void OffScreenManager::SetEffectSysytem(PostEffectType type_,
	std::unique_ptr<PostEffects::PostEffect> dst_)
{
	effectContainer[type_] = std::move(dst_);
}
