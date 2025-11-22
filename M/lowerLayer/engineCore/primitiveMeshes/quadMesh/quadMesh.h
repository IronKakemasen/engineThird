#pragma once

#include "../PrimitiveMeshCommon.h"

struct QuadMesh :PrimitiveMeshCommon
{
	virtual void Create(ID3D12Device* device_) override;
	QuadMesh();
};