#pragma once
#include <vector>

class PostEffectBuffer;
class TextureDataManager;

class OffScreenBehavior
{
protected:
	std::vector<PostEffectBuffer*> buffers;
	int shaderSetIndex{};

public:
	OffScreenBehavior(TextureDataManager* textureDataManager_, int numRequired_);
	virtual void Init() = 0;
	virtual void Update() = 0;
	PostEffectBuffer* GetBuffer(int index_);
	std::vector<uint16_t> WatchTextureIndexes();
	int WathchShaderSetIndex();

};

class OffScreen:public OffScreenBehavior
{

public:
	virtual void Init()override {};
	virtual void Update()override {};
	OffScreen(TextureDataManager* textureDataManager_, int numRequired_);
};


class OriginalScreen:public OffScreen
{

public:
	virtual void Init() override;
	virtual void Update() override;
	OriginalScreen(TextureDataManager* textureDataManager_, int numRequired_);

};

