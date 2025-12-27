#include "MeshForModelCommon.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>

void MeshAndDataCommon::CreatePSO(AllPipelineSet* allPipelineset_)
{
	static bool onlyOnce = true;

	if (onlyOnce)
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

				descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
					"TANGENT",
					0,
					DXGI_FORMAT_R32G32B32_FLOAT,
					D3D12_APPEND_ALIGNED_ELEMENT
				));


				return descs;

		};

		auto modelSimpleRP = []()
		{

			std::vector<D3D12_ROOT_PARAMETER> meters;

			static D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
			RootSignatureCreator::SetDescriptorRange(&descriptorRange[0],
				D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				0);

			meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
				descriptorRange,
				D3D12_SHADER_VISIBILITY_PIXEL,
				1));

			meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(0));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(1));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(2));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(3));


			return meters;
		};

		auto modelBumpRP = []() {

			std::vector<D3D12_ROOT_PARAMETER> meters;

			static D3D12_DESCRIPTOR_RANGE colorMapDR[1] = {};
			RootSignatureCreator::SetDescriptorRange(&colorMapDR[0],
				D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				0);

			meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
				colorMapDR,
				D3D12_SHADER_VISIBILITY_PIXEL,
				1));

			static D3D12_DESCRIPTOR_RANGE normalMapDR[1] = {};
			RootSignatureCreator::SetDescriptorRange(&normalMapDR[0],
				D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				1);

			meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
				normalMapDR,
				D3D12_SHADER_VISIBILITY_PIXEL,
				1));

			meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(0));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(1));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(2));
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(3));


			return meters;
		};


		std::string folderPath = "Model/";

		//modelSimple
		allPipelineset_->CreateNewPipeline(folderPath, "ModelSimple.VS", "ModelSimple.PS", inputLayOutFunc, modelSimpleRP);

		//modelBump
		allPipelineset_->CreateNewPipeline(folderPath, "ModelBump.VS", "ModelBump.PS", inputLayOutFunc, modelBumpRP);

		onlyOnce = false;
	}

}

