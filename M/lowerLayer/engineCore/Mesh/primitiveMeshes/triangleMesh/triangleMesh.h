#include "../PrimitiveMeshCommon.h"

struct TriangleMesh:PrimitiveMeshCommon
{
	virtual void Create(ID3D12Device* device_) override;
	TriangleMesh();
};