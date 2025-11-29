#include "M.h"
#include "./engineCore/VpShader/vpShaderTable/vpShaderTable.h"
#include "./engineCore/PSO/allPipelineSet.h"

void M::CreatePresetOfPipelines()
{
	CreateMobilePrimitiveMeshPipeline();
	CreateTestParticle2DPipeline();
}

void M::CreateMobilePrimitiveMeshPipeline()
{
	auto inputLayOutFunc = []()
		{
			std::vector<D3D12_INPUT_ELEMENT_DESC> descs;
			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"TEXCOORD",
				0,
				DXGI_FORMAT_R32G32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"NORMAL",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			return descs;

		};

	auto rootparameterFunc = []() {

		std::vector<D3D12_ROOT_PARAMETER> meters;

		static D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
		RootSignatureCreator::SetDescriptorRange(&descriptorRange[0],
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			0);

		meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
			descriptorRange,
			D3D12_SHADER_VISIBILITY_PIXEL,
			1));

		//meters.emplace_back(RootSignatureCreator::GetRootParaMeterDescriptorRange());
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(0));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(1));
		//meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(2));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(2));
		//meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(4));

		return meters;
		};

	CreateNewPipelineSet("MobilePrimitiveMesh.VS", "MobilePrimitiveMesh.PS", inputLayOutFunc, rootparameterFunc);
}


void M::CreateTestParticle2DPipeline()
{
	auto inputLayoutFunc = []()
		{
			std::vector<D3D12_INPUT_ELEMENT_DESC> descs;
			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"TEXCOORD",
				0,
				DXGI_FORMAT_R32G32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
				"NORMAL",
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,
				D3D12_APPEND_ALIGNED_ELEMENT
			));

			return descs;
		};

	auto rootparameterFunc = []() {

		std::vector<D3D12_ROOT_PARAMETER> meters;

		static D3D12_DESCRIPTOR_RANGE descriptorRangeForMatrices[1] = {};
		//static D3D12_DESCRIPTOR_RANGE descriptorRangeForTexture[1] = {};

		RootSignatureCreator::SetDescriptorRange(&descriptorRangeForMatrices[0],
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			0);

		//RootSignatureCreator::SetDescriptorRange(&descriptorRangeForTexture[0],
		//	D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
		//	1);

		//matrices
		meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
			descriptorRangeForMatrices,
			D3D12_SHADER_VISIBILITY_VERTEX,
			1));

		////テクスチャ
		//meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
		//	descriptorRange2,
		//	D3D12_SHADER_VISIBILITY_PIXEL,
		//	1));

		//Material
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(0));

		return meters;
		};

	CreateNewPipelineSet("TestParticle2D.VS", "TestParticle2D.PS", inputLayoutFunc, rootparameterFunc);
}