#pragma once
#include "../descriptorHeapBehavior.h"

struct DsvDescriptorHeap :DescriptorHeapBehavior
{
	virtual void Init(ID3D12Device* device_, uint8_t numDescriptors_)override;
};

