#pragma once
#include "../SrvCreatorBehavior.h"
#include <wrl.h>
#include <d3d12.h>
#include <memory>

class PostEffectBuffer;

class PostEffectSrCreator :public SrvCreatorBehavior
{
	D3D12_SHADER_RESOURCE_VIEW_DESC CreateSrvDesc();
	void CreateSRVForPostEffect(PostEffectBuffer* data_);
	void CreteResource(PostEffectBuffer* data_);

public:

	std::unique_ptr<PostEffectBuffer> Create();
	PostEffectSrCreator();

};
