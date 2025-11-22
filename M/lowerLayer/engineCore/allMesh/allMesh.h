#pragma once
#include "../primitiveMeshes/triangleMesh/triangleMesh.h"
#include "../primitiveMeshes/quadMesh/quadMesh.h"

class AllMesh
{
	std::unique_ptr<TriangleMesh> triangleMesh;
	std::unique_ptr<QuadMesh> quadMesh;

public:

	void Init(ID3D12Device* device_);

};

