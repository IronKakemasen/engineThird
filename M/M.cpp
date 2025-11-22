#include "M.h"

M* M::GetInstance()
{
	static M m;
	return &m;
}

int M::GetTexIndex(TextureTag tag_)
{
	return resourceContainer.GetTextureIndex(tag_);
}

void M::Init(TextureDataManager* textureDataManager_)
{
	if (initOnlyOnce)
	{
		resourceContainer.Init(textureDataManager_);
	}

	initOnlyOnce = false;
}