#include "textureDataCreator.h"
#include "../../logAndException/outputDebugLog.h"
#include <vector>
#include "../../gpuResources/shaderBuffer/shaderBuffer.h"
#include "../../allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../../bufferAndMap/bufferAndMap.h"

TextureDataCreator::TextureDataCreator()
{

}

int TextureDataCreator::CreateShaderBufferFromFile(std::string filePath_)
{
	ShaderBuffer texData;

	auto mipImages = texData.LoadTextureFile(filePath_);
	auto metaData = mipImages.GetMetadata();

	texData.CreateTextureResourceFromMetaData(device, metaData);

	texData.UploadTextureData(
		device,
		commandList,
		mipImages);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = 
		texData.CreateSRVDescFromTexture(metaData.format, metaData.mipLevels);

	texData.CreateSRV(device, srvDescriptorHeap, srvDesc);

	shaderBufferData.emplace_back(texData);

	return ShaderBuffer::cur_index - 1;
}


void TextureDataCreator::Init(SrvDescriptorHeap* srvDescriptorHeap_ , ID3D12Device* device_, ID3D12GraphicsCommandList* commandList_)
{
	device = device_;
	commandList = commandList_;
	srvDescriptorHeap = srvDescriptorHeap_;


}

