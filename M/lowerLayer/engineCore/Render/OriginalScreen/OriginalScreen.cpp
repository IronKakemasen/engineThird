#include "OriginalScreen.h"
#include "../engineCore/textureDataManager/textureDataManager.h"
#include "../M.h"

OffScreenBehavior::OffScreenBehavior(TextureDataManager* textureDataManager_, int numRequired_)
{
	for (int i = 0; i < numRequired_; ++i)
	{
		buffers.emplace_back(textureDataManager_->CreatePostEffectBuffer());
	}
}

PostEffectBuffer* OffScreenBehavior::GetBuffer(int index_)
{
	return buffers[index_];
}

std::vector<uint16_t> OffScreenBehavior::WatchTextureIndexes()
{
	std::vector<uint16_t> ret;
	for (auto* it : buffers)
	{
		if (it)
		{
			ret.emplace_back(*it->GetSrvHandle());
		}
	}
	return ret;
}

int OffScreenBehavior::WathchShaderSetIndex()
{
	return shaderSetIndex;
}


OffScreen::OffScreen(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreenBehavior(textureDataManager_, numRequired_) {
};


OriginalScreen::OriginalScreen(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
};

void OriginalScreen::Init()
{
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("NoEffection.VS", "NoEffection.PS");

}

void OriginalScreen::Update()
{

}
