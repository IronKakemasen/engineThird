#pragma once
#include "../../OriginalScreen/OriginalScreen.h"
#include "../../../Buffer/constantBuffer/SimpleNeonLikeBuffer/SimpleNeonLikeBuffer.h"
class PostEffectBuffer;
class TextureDataManager;

namespace PostEffects
{
	struct Bloom :public OffScreen
	{
		virtual void Update()override;
		virtual void Init(ID3D12Device* device_) override;
		Bloom(TextureDataManager* textureDataManager_, int numRequired_);
	};


	struct NoEffection :public OffScreen
	{
		virtual void Update()override;
		virtual void Init(ID3D12Device* device_) override;
		NoEffection(TextureDataManager* textureDataManager_, int numRequired_);

	};

	struct GreyScale :public OffScreen
	{
		virtual void Update()override;
		virtual void Init(ID3D12Device* device_) override;
		GreyScale(TextureDataManager* textureDataManager_, int numRequired_);
	};

	class SimpleNeonLike :public OffScreen
	{
		SimpleNeonLikePara para;
		SimpleNeonLikeBuffer cBuffer;

	public:
		virtual void Update()override;
		virtual void Init(ID3D12Device* device_) override;
		SimpleNeonLike(TextureDataManager* textureDataManager_, int numRequired_);
	};

	
}
