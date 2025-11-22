#include "shaderBuffer.h"
#include "../../allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
#include "../../../../utilities/convertString/convertString.h"
#include "../../bufferAndMap/bufferAndMap.h"
#include "../../CommandControl/CommandControl.h"

D3D12_SHADER_RESOURCE_VIEW_DESC ShaderBuffer::CreateSRVDescFromTexture(
	DXGI_FORMAT metaDataFormat_, size_t mipLevels_)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metaDataFormat_;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(mipLevels_);
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.PlaneSlice = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	return srvDesc;
}


void ShaderBuffer::CreateSRV(ID3D12Device* device_, SrvDescriptorHeap* descriptorHeap_,
	D3D12_SHADER_RESOURCE_VIEW_DESC desc_)
{
	//テクスチャハンドル
	if (cur_index > 0)
	{
		handle.ptr = descriptorHeap_->GetCPUDescriptorHandle(cur_index);
		handleGPU.ptr = descriptorHeap_->GetGPUDescriptorHandle(cur_index);

		device_->CreateShaderResourceView(resource.Get(), &desc_, handle);

	}
	else
	{
		handle = descriptorHeap_->Getter_Descriptorheap()->GetCPUDescriptorHandleForHeapStart();
		handleGPU = descriptorHeap_->Getter_Descriptorheap()->GetGPUDescriptorHandleForHeapStart();
	}

	cur_index++;
	if (cur_index > descriptorHeap_->Getter_MaxDescriptor()) assert(false);
}

void ShaderBuffer::UploadTextureData(
	ID3D12Device* device_, CommandControl* CommandControl_,
	DirectX::ScratchImage const& mipImages_)
{
	std::vector<D3D12_SUBRESOURCE_DATA> subresource;

	DirectX::PrepareUpload(device_, mipImages_.GetImages(),
		mipImages_.GetImageCount(), mipImages_.GetMetadata(), subresource);

	UINT intermediateSize = static_cast<UINT>(GetRequiredIntermediateSize(resource.Get(), 0, UINT(subresource.size())));

	intermediateResource = CreateBufferResource(device_, intermediateSize);

	CommandControl_->PrepareForNextCommandList();

	UpdateSubresources(CommandControl_->Getter_commandList(), resource.Get(), intermediateResource.Get(), 0, 0,
		UINT(subresource.size()), subresource.data());
	//Textureへの転送後は利用できるよう、D3D2_RESOUTRCE_STATE_COPY_DESTから
	//D3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変更する
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource.Get();
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;

	CommandControl_->Getter_commandList()->ResourceBarrier(1, &barrier);

	CommandControl_->Getter_commandList()->Close();
}


//テクスチャを読み込むための関数
DirectX::ScratchImage ShaderBuffer::LoadTextureFile(std::string const& filePath_)
{
	//テクスチャファイルを読み込んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath_);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(),
		DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	//ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		DirectX::TEX_FILTER_SRGB, 0,
		mipImages);

	assert(SUCCEEDED(hr));

	//ミップマップ付きのデータを返す
	return mipImages;
}

ShaderBuffer::ShaderBuffer()
{
#ifdef USE_IMGUI
	cur_index += 1;
#endif // #ifdef USE_IMGUI

}

void ShaderBuffer::CreateTextureResourceFromMetaData(
	ID3D12Device* device_,
	DirectX::TexMetadata& metaData_)
{
	D3D12_RESOURCE_DESC resourceDesc{};

	//[ materialDataを元にResourceの設定 ]
	//textureの幅
	resourceDesc.Width = UINT(metaData_.width);
	//textureの高さ
	resourceDesc.Height = UINT(metaData_.height);
	//mipmapの数
	resourceDesc.MipLevels = UINT16(metaData_.mipLevels);
	//奥行orTextureの配列数
	resourceDesc.DepthOrArraySize = UINT16(metaData_.arraySize);
	//Textureのformat
	resourceDesc.Format = metaData_.format;
	//DXGI_FORMAT_B8G8R8A8_UNORM_SRGB
	//サンプリングカウント。１固定
	resourceDesc.SampleDesc.Count = 1;
	//テクスチャの次元数。2
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metaData_.dimension);

	//[ 利用するHeapの設定 ]
	//細かい設定を行う
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	//[ resourceを生成する ]
	HRESULT hr = device_->CreateCommittedResource(
		&heapProperties,					//Heapの設定
		D3D12_HEAP_FLAG_NONE,				//Heapの特殊な設定、特になし
		&resourceDesc,						//Resourceの設定
		D3D12_RESOURCE_STATE_COPY_DEST,		//データ転送される設定
		nullptr,							//Clear最適値。使わないのでnullptr
		IID_PPV_ARGS(&resource));			//作成するresourceへのポインタのポインタ

	assert(SUCCEEDED(hr));

}
