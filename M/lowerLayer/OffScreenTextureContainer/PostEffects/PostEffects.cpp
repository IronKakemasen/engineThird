#include "PostEffects.h"
#include "../engineCore/textureDataManager/textureDataManager.h"

void PostEffects::Bloom::operator()()
{

}

void PostEffects::Bloom::Init(TextureDataManager* textureDataManager_)
{
	for (int i = 0; i < 3; ++i)
	{
		buffers.emplace_back(textureDataManager_->CreatePostEffectBuffer());
	}
}
