#pragma once
#include "../textureDataCreator/textureDataCreator.h"
#include "../../gpuResources/shaderBuffer/shaderBuffer.h"

struct SrvDescriptorHeap;

enum class TextureTag
{

};

class TextureDataManager
{
public:


	std::unordered_map<TextureTag, int> map_textureID;
	void Init(SrvDescriptorHeap* srvDescriptorHeap_ , ID3D12Device* device_, ID3D12GraphicsCommandList* commandList_);
	void CreateTextureFromFile(TextureTag tag_, std::string filePath_);

private:
	TextureDataCreator textureDataCreator;

};

