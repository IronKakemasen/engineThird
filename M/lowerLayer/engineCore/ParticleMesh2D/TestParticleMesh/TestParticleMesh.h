#pragma once
#include "../ParticleMesh2DCommon.h"

struct TestParticleMesh:ParticleMesh2DCommon
{
public:
	virtual void Create(ID3D12Device* device_, ParticleMeshSrvCreator* particleMeshSrvCreator_) override;
	TestParticleMesh();
};

