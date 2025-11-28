#include "allMesh.h"

void AllMesh::ResetDrawIndexes()
{
	triangleMesh->DrawIndexReset();
	quadMesh->DrawIndexReset();
}

void AllMesh::Init(ID3D12Device* device_, ParticleMeshSrvCreator* ParticleMeshSrvCreator_)
{
	static bool initOnlyOnce = true;
	if (initOnlyOnce)
	{
		triangleMesh.reset(new TriangleMesh);
		quadMesh.reset(new QuadMesh);
		//testParticleMesh.reset(new TestParticleMesh);

		triangleMesh->Create(device_);
		quadMesh->Create(device_);
		//testParticleMesh->Create(device_,ParticleMeshSrvCreator_);

		initOnlyOnce = false;
	}
}