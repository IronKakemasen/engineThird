#pragma once
#include "PostEffectType.h"
#include "../../utilities/vectorAndMatrix/vectorAndMatrix.h"
#include <unordered_map>
#include <d3d12.h>

class OriginalScreen;
class Palette
{
	class Para
	{

	public:

		int shaderSetIndex;
		std::vector<uint16_t> offscreenTextureContainer;
		std::vector<D3D12_GPU_VIRTUAL_ADDRESS> cBufferAddressContainer;
		Para();
	};

	PostEffectType curType;
	std::unordered_map < PostEffectType, Para> paraContainer;
	OriginalScreen* originalScreen = nullptr;
public:
	void Init(OriginalScreen* originalScreen_);
	Palette();
	int WatchShaderSetIndex();
	std::vector<uint16_t> WatchUseTexture();
	std::vector<D3D12_GPU_VIRTUAL_ADDRESS> WatchCBufferAddressContainer();

	void Set(PostEffectType type_, std::vector<uint16_t> textures_, 
		int shaderSetIndex_, std::vector<D3D12_GPU_VIRTUAL_ADDRESS> cBufferAddressContainer_);
	void ChangeType(PostEffectType type_);
};

