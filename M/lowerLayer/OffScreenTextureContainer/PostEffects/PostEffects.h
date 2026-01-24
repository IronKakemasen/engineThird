#pragma once
#include <vector>

class PostEffectBuffer;
class TextureDataManager;

namespace PostEffects
{
	struct PostEffectBehavior
	{
		virtual void operator()() = 0;
		virtual void Init(TextureDataManager* textureDataManager_) = 0;
	protected:
		std::vector<PostEffectBuffer*> buffers;
	};

	struct PostEffect:public PostEffectBehavior
	{
		virtual void operator()()override {};
		virtual void Init(TextureDataManager* textureDataManager_) override {};

	};

	struct Bloom :public PostEffect
	{
		virtual void operator()()override;
		virtual void Init(TextureDataManager* textureDataManager_) override;

	};

	struct NoEffection :public PostEffect
	{
		virtual void operator()()override;
		virtual void Init(TextureDataManager* textureDataManager_) override;

	};


};

