#include "inputLayoutDescCreator.h"
#pragma comment(lib,"d3d12.lib")



void InputLayoutDescCreator::SetInputElementDescs(std::string shaderSetName_)
{

	UINT numElements = 0;

	if (shaderSetName_ == "Default,Default")
	{
		numElements = 3;
		heap_inputElementDescs.second = numElements;

		heap_inputElementDescs.first = new D3D12_INPUT_ELEMENT_DESC[numElements];

		heap_inputElementDescs.first[0] = GetInputElementDesc(
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		);

		heap_inputElementDescs.first[1] = GetInputElementDesc(
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		);

		heap_inputElementDescs.first[2] = GetInputElementDesc(
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		);


	}


}

D3D12_INPUT_ELEMENT_DESC InputLayoutDescCreator::GetInputElementDesc(
	LPCSTR semanticName_,
	UINT semanticIndex_,
	DXGI_FORMAT format_,
	UINT alignedByteOffset_
)
{
	D3D12_INPUT_ELEMENT_DESC ret_elementDesc = {};

	ret_elementDesc.SemanticName = semanticName_;
	ret_elementDesc.SemanticIndex = semanticIndex_;
	ret_elementDesc.Format = format_;
	ret_elementDesc.AlignedByteOffset = alignedByteOffset_;

	return ret_elementDesc;
}

D3D12_INPUT_LAYOUT_DESC InputLayoutDescCreator::CreateInputLayoutDesc(std::string shaderSetName_)
{
	D3D12_INPUT_LAYOUT_DESC ret_inputLayoutDesc = {};
	SetInputElementDescs(shaderSetName_);


	ret_inputLayoutDesc.pInputElementDescs = heap_inputElementDescs.first;
	ret_inputLayoutDesc.NumElements = heap_inputElementDescs.second;;


	return ret_inputLayoutDesc;
}


void InputLayoutDescCreator::SafeRelease()
{
	if (heap_inputElementDescs.first)
	{
		delete[] heap_inputElementDescs.first;
		heap_inputElementDescs.second = 0;
	}
}
