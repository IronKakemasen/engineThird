#pragma once
#include <string>
#include <wrl.h>
#include <d3d12.h>

#include "../../../../../external/DirectXTex/d3dx12.h"
#include "../../../../../external/DirectXTex/DirectXTex.h"


struct ShaderBuffer;
struct SrvDescriptorHeap;
class CommandControl;

struct TextureDataCreator
{
public:
	int CreateShaderBufferFromFile(std::string filePath_);
	void Init(SrvDescriptorHeap* srvDescriptorHeap_ , ID3D12Device* device_, CommandControl* commandControl_);
	TextureDataCreator();

private:
	std::vector<ShaderBuffer >shaderBufferData;
	ID3D12Device* device = nullptr;
	CommandControl* commandControl = nullptr;;
	SrvDescriptorHeap* srvDescriptorHeap = nullptr;


public:
	inline auto* Getter_ShaderBufferData()
	{
		return &shaderBufferData;
	}


};
