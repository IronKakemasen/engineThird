#include "allMesh.h"

void AllMesh::ResetDrawIndexes()
{
	triangleMesh->DrawIndexReset();
	quadMesh->DrawIndexReset();
}

void AllMesh::Init(ID3D12Device* device_)
{
	static bool initOnlyOnce = true;
	if (initOnlyOnce)
	{
		triangleMesh.reset(new TriangleMesh);
		quadMesh.reset(new QuadMesh);

		triangleMesh->Create(device_);
		quadMesh->Create(device_);

		initOnlyOnce = false;
	}
}