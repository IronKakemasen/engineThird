#pragma once

#include <wrl.h>
#include <d3d12.h>
#include<stdint.h>

class GPUResourceBehavior
{
public:
	//[ currentDescriptorUsingIndex ]
	static inline uint16_t cur_index = 0;

protected:
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = { nullptr };
	D3D12_CPU_DESCRIPTOR_HANDLE handle;

public:

	inline auto** Getter_ResourcePP()
	{
		return resource.GetAddressOf();
	}


	inline auto* Getter_Resource()
	{
		return resource.Get();
	}

	inline auto* Getter_Handle()
	{
		return &handle;
	}


};

