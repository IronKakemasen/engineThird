#pragma once
#include "../gpuResources/Resource/shaderBuffer/shaderBuffer.h"
#include "../gpuResources/Resource/gpuResourcesBehavior.h"
#include <assert.h>
#include <memory>

template <typename T>
struct StructuredBufferAndMap
{
private:
	std::unique_ptr<ShaderBuffer> shaderBuffer;

public:
	T* buffMap = nullptr;

	void CreateAndMapping(ID3D12Device* device_,UINT maxCreateNum_)
	{
		//リソースのサイズ
		UINT sizeOfBuffer = static_cast<UINT>(sizeof(T)* maxCreateNum_);
		//Resourceの生成
		shaderBuffer = CreateBufferResource(device_, sizeOfBuffer);
		//書き込むためのアドレスを取得
		HRESULT hr = shaderBuffer->Map(0, nullptr, reinterpret_cast<void**>(&buffMap));
		SUCCEEDED(hr);
	}

};



