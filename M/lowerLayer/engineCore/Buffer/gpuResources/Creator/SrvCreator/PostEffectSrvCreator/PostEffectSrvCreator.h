#pragma once
#include "../SrvCreatorBehavior.h"
#include <wrl.h>
#include <d3d12.h>

class PostEffectBuffer;

class PostEffectSrvCreator :public SrvCreatorBehavior
{
	D3D12_SHADER_RESOURCE_VIEW_DESC CreateSrvDesc();

public:

	uint16_t CreateSRVForPostEffect(PostEffectBuffer* data_);
	PostEffectSrvCreator();

};
