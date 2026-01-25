#pragma once
#include "../../OriginalScreen/OriginalScreen.h"

class PostEffectBuffer;
class TextureDataManager;

namespace PostEffects
{
	struct Bloom :public OffScreen
	{
		virtual void Update()override;
		virtual void Init() override;
		Bloom(TextureDataManager* textureDataManager_, int numRequired_);
	};


	struct NoEffection :public OffScreen
	{
		virtual void Update()override;
		virtual void Init() override;
		NoEffection(TextureDataManager* textureDataManager_, int numRequired_);

	};

	struct GreyScale :public OffScreen
	{
		virtual void Update()override;
		virtual void Init() override;
		GreyScale(TextureDataManager* textureDataManager_, int numRequired_);

	};

}
