#include "ParticleMesh2DCommon.h"
#include "../../../PSO/allPipelineSet.h"
#include <assert.h>

void ParticleMesh2DCommon::CreatePSO(AllPipelineSet* allPipelineset_)
{
	static bool onlyOnce = true;
	if (onlyOnce)
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

			static D3D12_DESCRIPTOR_RANGE descriptorRangeForMatrices[1] = {};
			static D3D12_DESCRIPTOR_RANGE descriptorRangeForTexture[1] = {};

			RootSignatureCreator::SetDescriptorRange(&descriptorRangeForMatrices[0],
				D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				0);

			RootSignatureCreator::SetDescriptorRange(&descriptorRangeForTexture[0],
				D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
				1);

			//matrices
			meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
				descriptorRangeForMatrices,
				D3D12_SHADER_VISIBILITY_VERTEX,
				1));

			//テクスチャ
			meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
				descriptorRangeForTexture,
				D3D12_SHADER_VISIBILITY_PIXEL,
				1));

			//Material
			meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(0));

			return meters;
			};

		std::string folderPath = "Particle2D/";

		allPipelineset_->CreateNewPipeline(folderPath, "TestParticle2D.VS", "TestParticle2D.PS", inputLayoutFunc, rootparameterFunc);
		onlyOnce = false;
	}
}


ParticleMesh2DCommon::ParticleMesh2DCommon()
{
	vertexCnt = 4;
	indexCnt = 6;
}

void ParticleMesh2DCommon::Init(uint16_t kMaxDraw_, float width_, float height_, AllPipelineSet* allPipelineset_)
{
	kMaxDraw = kMaxDraw_;
	width = width_;
	height = height_;

	CreatePSO(allPipelineset_);
}

void ParticleMesh2DCommon::DetectOverDrawing(int sum_draw_)
{
	assert(sum_draw_ <= kMaxDraw);

}
