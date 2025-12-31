#pragma once
#include "./TextureSrvCreator/TextureSrvCreator.h"
#include "./ParticleMeshSrvCreator/ParticleMeshSrvCreator.h"
#include "./StructuredBufferSrvCreator/StructuredBufferSrvCreator.h"

struct ShaderBuffer;
struct SrvDescriptorHeap;
class CommandControl;
struct ShaderBufferData;
struct ID3D12Device;

class SrvCreator
{
	TextureSrvCreator textureSrvCreator;
	ParticleMeshSrvCreator particleMeshSrvCreator;
	StructuredBufferSrvCreator stBufferCretaor;

public:
	void Init(SrvDescriptorHeap* srvDescriptorHeap_, ID3D12Device* device_,
		CommandControl* commandControl_, ShaderBufferData* shaderBufferData_);

	auto* Getter_ParticleMeshSrvCreator()
	{
		return &particleMeshSrvCreator;
	}

	auto* Getter_TextureSrvCreator()
	{
		return &textureSrvCreator;
	}

	auto* Getter_StBufferCretaor()
	{
		return &stBufferCretaor;
	}

};

