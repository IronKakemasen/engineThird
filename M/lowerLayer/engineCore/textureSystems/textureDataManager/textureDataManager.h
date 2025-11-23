#pragma once
#include "../textureDataCreator/textureDataCreator.h"
#include "../../gpuResources/shaderBuffer/shaderBuffer.h"

struct SrvDescriptorHeap;
class CommandControl;

class TextureDataManager
{
public:
	void Init(SrvDescriptorHeap* srvDescriptorHeap_ , ID3D12Device* device_, CommandControl* commandControl_);
	int CreateTextureFromFile(std::string filePath_);

private:
	TextureDataCreator textureDataCreator;
public:
	inline auto* Getter_ShaderData()
	{
		return textureDataCreator.Getter_ShaderBufferData();
	}

};

