#pragma once
#include "../gpuResourcesBehavior.h"
#include "../../../../../external/DirectXTex/d3dx12.h"
#include "../../../../../external/DirectXTex/DirectXTex.h"

struct SrvDescriptorHeap;

struct ShaderBuffer :GPUResourceBehavior
{
	//[ currentDescriptorUsingIndex ]
	static inline uint16_t cur_index = 0;
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU;
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource;

public:
	ShaderBuffer();

	void CreateTextureResourceFromMetaData(
		ID3D12Device* device_,
		DirectX::TexMetadata& metaData_);

	//テクスチャを読み込むための関数
	DirectX::ScratchImage LoadTextureFile(std::string const& filePath_);

	void UploadTextureData(
		ID3D12Device* device_, ID3D12GraphicsCommandList* commandList_,
		DirectX::ScratchImage const& mipImages_);

	void CreateSRV(ID3D12Device* device_, SrvDescriptorHeap* descriptorHeap_,
		D3D12_SHADER_RESOURCE_VIEW_DESC desc_);

	D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRVDescFromTexture(DXGI_FORMAT metaDataFormat_, size_t mipLevels_);

};

