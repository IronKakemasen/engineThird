#pragma once
#include <vector>
#include <d3d12.h>

class PostEffectBuffer;
class TextureDataManager;
class OffScreenBehavior
{
protected:
	std::vector<PostEffectBuffer*> buffers;
	std::vector<D3D12_GPU_VIRTUAL_ADDRESS> cBufferAddressContainer;
	int shaderSetIndex{};

public:
	OffScreenBehavior(TextureDataManager* textureDataManager_, int numRequired_);
	virtual void Init(ID3D12Device* device_) = 0;
	virtual void Update() = 0;
	PostEffectBuffer* GetBuffer(int index_);
	std::vector<uint16_t> WatchTextureIndexes();
	int WathchShaderSetIndex();
	std::vector<D3D12_GPU_VIRTUAL_ADDRESS> WatchAddessContainer();
};

class OffScreen:public OffScreenBehavior
{

public:
	virtual void Init(ID3D12Device* device_)override {};
	virtual void Update()override {};
	OffScreen(TextureDataManager* textureDataManager_, int numRequired_);
};


class OriginalScreen:public OffScreen
{

public:
	virtual void Init(ID3D12Device* device_) override;
	virtual void Update() override;
	OriginalScreen(TextureDataManager* textureDataManager_, int numRequired_);

};

