#include "PrimitiveMeshCommon.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>

void PrimitiveMeshCommon::Init(uint16_t kMaxDraw_, UINT vertexCnt_, UINT indexCnt_, AllPipelineSet* allPipelineset_)
{
	vertexCnt = vertexCnt_;
	indexCnt = indexCnt_;
	materialBuffer.resize(kMaxDraw_);
	worldMatrixBuffer.resize(kMaxDraw_);
	wvpMatrixBuffer.resize(kMaxDraw_);
	kMaxDraw = kMaxDraw_;

	CreatePSO(allPipelineset_);

}

void PrimitiveMeshCommon::DrawIndexReset()
{
	cur_drawIndex = 0;
}

void PrimitiveMeshCommon::DetectOverDrawing()
{
	assert(cur_drawIndex < kMaxDraw);
}

void PrimitiveMeshCommon::CreatePSO(AllPipelineSet* allPipelineset_)
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

		std::string folderPath = "MobilePrimitive/";

		allPipelineset_->CreateNewPipeline(folderPath, "MobilePrimitiveMesh.VS", "MobilePrimitiveMesh.PS", inputLayOutFunc, rootparameterFunc);
		onlyOnce = false;
	}
}