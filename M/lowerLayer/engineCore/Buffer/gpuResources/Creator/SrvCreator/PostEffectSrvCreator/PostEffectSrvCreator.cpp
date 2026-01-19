#include "PostEffectSrvCreator.h"
#include <assert.h>
#include "../../commonVariables.h"
#include "../../../Data/ShaderBufferData/ShaderBufferData.h"
#include "../../Buffer/PostEffectBuffer/PostEffectBuffer.h"

PostEffectSrvCreator::PostEffectSrvCreator()
{

}

D3D12_SHADER_RESOURCE_VIEW_DESC PostEffectSrvCreator::CreateSrvDesc()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(1);
	//srvDesc.Texture2D.MostDetailedMip = 0;//

	////[ materialDataを元にResourceの設定 ]
	////textureの幅
	//resourceDesc.Width = UINT(CommonV::kWindow_W);
	////textureの高さ
	//resourceDesc.Height = UINT(CommonV::kWindow_H);
	////mipmapの数
	//resourceDesc.MipLevels = 1;
	////奥行orTextureの配列数
	//resourceDesc.DepthOrArraySize = 1;
	////Textureのformat
	//resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	////サンプリングカウント。１固定
	//resourceDesc.SampleDesc.Count = 1;
	////テクスチャの次元数。2
	//resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(3);
	//resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	return srvDesc;
}

uint16_t PostEffectSrvCreator::CreateSRVForPostEffect(PostEffectBuffer* data_)
{

	D3D12_SHADER_RESOURCE_VIEW_DESC desc = CreateSrvDesc();
	uint16_t ret_index = CreateSRV(desc, data_->GetShaderBuffer());

	shaderBufferData->gpuHandleContainer.emplace_back(data_->GetShaderBuffer()->handleGPU);

#ifdef USE_IMGUI
	return ret_index - 1;
#endif // USE_IMGUI

	return ret_index;
}
