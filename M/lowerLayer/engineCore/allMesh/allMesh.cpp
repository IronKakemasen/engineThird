#include "allMesh.h"

void AllMesh::Init(ID3D12Device* device_)
{
	triangleMesh.reset(new TriangleMesh);
	quadMesh.reset(new QuadMesh);

	triangleMesh->Create(device_);
	quadMesh->Create(device_);

}