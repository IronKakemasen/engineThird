#include "textureDataCreator.h"
#include "../../logAndException/outputDebugLog.h"
#include <vector>
#include "../../gpuResources/shaderBuffer/shaderBuffer.h"
#include "../../allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../../bufferAndMap/bufferAndMap.h"
#include "../../CommandControl/CommandControl.h"

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
		commandControl,
		mipImages);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = 
		texData.CreateSRVDescFromTexture(metaData.format, metaData.mipLevels);

	texData.CreateSRV(device, srvDescriptorHeap, srvDesc);

	shaderBufferData.emplace_back(texData);

#ifdef USE_IMGUI
	return ShaderBuffer::cur_index - 2;
#endif // USE_IMGUI

	return ShaderBuffer::cur_index - 1 ;

}


void TextureDataCreator::Init(SrvDescriptorHeap* srvDescriptorHeap_ , ID3D12Device* device_, CommandControl* commandControl_)
{
	device = device_;
	commandControl = commandControl_;
	srvDescriptorHeap = srvDescriptorHeap_;


}

