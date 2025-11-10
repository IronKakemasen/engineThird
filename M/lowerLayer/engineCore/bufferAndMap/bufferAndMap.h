#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <assert.h>
#include <type_traits>

template <typename T>
struct BufferAndMap
{

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> buff = nullptr;

public:
	T* buffMap = nullptr;

	void CreateAndMapping(ID3D12Device* device_)
	{
		//リソースのサイズ
		UINT sizeOfBuffer = static_cast<UINT>(sizeof(std::remove_pointer<decltype(buffMap)>));

		//Resourceの生成
		buff = CreateBufferResource(device_, sizeOfBuffer);
		//書き込むためのアドレスを取得
		buff->Map(0, nullptr, reinterpret_cast<void**>(&buffMap));

	}


};


[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(
	ID3D12Device* device_, UINT sizeInByte_);
