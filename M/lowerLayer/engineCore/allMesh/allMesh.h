#pragma once
#include "../primitiveMeshes/triangleMesh/triangleMesh.h"
#include "../primitiveMeshes/quadMesh/quadMesh.h"

class AllMesh
{
	std::unique_ptr<TriangleMesh> triangleMesh;
	std::unique_ptr<QuadMesh> quadMesh;

	bool initOnlyOnce = true;
public:
	void Init(ID3D12Device* device_);

	inline auto* Getter_TriangleMesh()
	{
		return triangleMesh.get();
	}

	inline auto* Getter_QuadMesh()
	{
		return quadMesh.get();
	}


};

