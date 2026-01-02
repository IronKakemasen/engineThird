#include "MeshForModelCommon.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>

void MeshAndDataCommon::CreatePSO(AllPipelineSet* allPipelineset_)
{
	static bool onlyOnce = true;

	if (!onlyOnce) return;
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

		meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 0));
		meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 1));

		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::VS, 0));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 1));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 2));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 3));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 4));


		return meters;
	};

	auto modelBumpRP = []() {

		std::vector<D3D12_ROOT_PARAMETER> meters;

		meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 0));
		meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 1));
		meters.emplace_back(RootSignatureCreator::GetRootparameterSRV(ShaderStage::PS, 2));

		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::VS, 0));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 1));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 2));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 3));
		meters.emplace_back(RootSignatureCreator::GetRootparameterCBV(ShaderStage::PS, 4));

		return meters;
	};


	std::string folderPath = "Model/";

	//modelSimple
	allPipelineset_->CreateNewPipeline(folderPath, "ModelSimple.VS", "ModelSimple.PS", inputLayOutFunc, modelSimpleRP);
	//modelPhong
	allPipelineset_->CreateNewPipeline(folderPath, "ModelPhong.VS", "ModelPhong.PS", inputLayOutFunc, modelSimpleRP);
	//modelNormalizedPhong
	allPipelineset_->CreateNewPipeline(folderPath, "ModelNormalizedPhong.VS", "ModelNormalizedPhong.PS", inputLayOutFunc, modelSimpleRP);
	//modelBump
	allPipelineset_->CreateNewPipeline(folderPath, "ModelBump.VS", "ModelBump.PS", inputLayOutFunc, modelBumpRP);
	//ModelCookTorrance
	allPipelineset_->CreateNewPipeline(folderPath, "ModelCookTorrance.VS", "ModelCookTorrance.PS", inputLayOutFunc, modelSimpleRP);
	//ModelGGX
	allPipelineset_->CreateNewPipeline(folderPath, "ModelGGX.VS", "ModelGGX.PS", inputLayOutFunc, modelSimpleRP);

		
	onlyOnce = false;

}

