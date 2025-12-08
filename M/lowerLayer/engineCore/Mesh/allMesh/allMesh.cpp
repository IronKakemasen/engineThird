#include "allMesh.h"

void AllMesh::ResetDrawIndexes()
{
	triangleMesh->DrawIndexReset();
	quadMesh->DrawIndexReset();
}

void AllMesh::Init(ID3D12Device* device_, ParticleMeshSrvCreator* ParticleMeshSrvCreator_, AllPipelineSet* allPipelineSet_)
{
	static bool initOnlyOnce = true;
	if (initOnlyOnce)
	{
		triangleMesh.reset(new TriangleMesh(allPipelineSet_));
		quadMesh.reset(new QuadMesh(allPipelineSet_));
		testParticleMesh.reset(new TestParticleMesh(allPipelineSet_));

		triangleMesh->CreateMesh(device_);
		quadMesh->CreateMesh(device_);
		testParticleMesh->CreateMesh(device_,ParticleMeshSrvCreator_);

		initOnlyOnce = false;
	}
}