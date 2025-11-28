#pragma once
#include "../primitiveMeshes/triangleMesh/triangleMesh.h"
#include "../primitiveMeshes/quadMesh/quadMesh.h"
#include "../ParticleMesh2D/TestParticleMesh/TestParticleMesh.h"

class ParticleMeshSrvCreator;

class AllMesh
{
	std::unique_ptr<TriangleMesh> triangleMesh;
	std::unique_ptr<QuadMesh> quadMesh;
	std::unique_ptr<TestParticleMesh> testParticleMesh;

public:

	void ResetDrawIndexes();
	void Init(ID3D12Device* device_, ParticleMeshSrvCreator* ParticleMeshSrvCreator_);

	inline auto* Getter_TestParticleMesh()
	{
		return testParticleMesh.get();
	}

	inline auto* Getter_TriangleMesh()
	{
		return triangleMesh.get();
	}

	inline auto* Getter_QuadMesh()
	{
		return quadMesh.get();
	}


};

