#pragma once
#include <d3d12.h>
#include "../pipelineComponents.h"
#include <string>

class InputLayoutDescCreator
{	
	std::pair<D3D12_INPUT_ELEMENT_DESC*, UINT> heap_inputElementDescs = { nullptr ,0};

	D3D12_INPUT_ELEMENT_DESC GetInputElementDesc(
		LPCSTR semanticName_,
		UINT semanticIndex_,
		DXGI_FORMAT format_,
		UINT alignedByteOffset_
	);

	//いつか修正
	void SetInputElementDescs(std::string shaderSetName_);

public:

	D3D12_INPUT_LAYOUT_DESC CreateInputLayoutDesc(std::string shaderSetName_);
	void SafeRelease();
};

