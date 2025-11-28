#include "M.h"
#include "./engineCore/Render/ExclusiveDraw/ExclusiveDraw.h"
#include "./engineCore/Render/CommonDrawingSystem/CommonDrawSystem.h"
#include "./engineCore/WinApp.h"
#include "./engineCore/VpShader/vpShaderTable/vpShaderTable.h"
#include "./engineCore/PSO/allPipelineSet.h"

void M::DrawInstancingParticle2D(int numParticles_, Vector4 color_, int texHandle_,
	BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
	std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_)
{
	exclusiveDraw->DrawInstancingParticle2D(numParticles_, color_, texHandle_,
		blendMode_, cullMode_, shaderSet_,
		trans_, uvTrans_, vpMat_);
}


void M::DrawMTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_,int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	exclusiveDraw->DrawMobileTriangle(left_, top_, right_,
		color_, texHandle_, drawMode_, blendMode_, cullMode_, shaderSet_,
		trans_, uvTrans_, vpMat_);
}

void M::DrawMQuad(VertexData& leftTop_, VertexData& rightTop_, VertexData& rightBottom_, VertexData& leftBottom_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	exclusiveDraw->DrawMobileQuad(leftTop_, rightTop_, rightBottom_, leftBottom_,
		color_, texHandle_, drawMode_, blendMode_, cullMode_, shaderSet_,
		trans_, uvTrans_, vpMat_);
}

void M::CreateNewPipelineSet(
	std::string vsFileName_,std::string psFileName_,
	std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> inputElementDescCreateFunc_,
	std::function<std::vector<D3D12_ROOT_PARAMETER>()> rootParameterCreateFunc_)
{
	allPipelineSet->CreateNewPipeline(vsFileName_, psFileName_,
		inputElementDescCreateFunc_, rootParameterCreateFunc_);
}


M* M::GetInstance()
{
	static M m;
	return &m;
}

int M::GetTexIndex(TextureTag tag_)
{
	return resourceContainer.GetTextureIndex(tag_);
}

int M::GetShaderSetIndexFromFileName(std::string vertexShader_, std::string pixelShader_)
{
	return vpShaderTable->GetIDFromTableName(vertexShader_ + " + " +  pixelShader_);
}


void M::Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, VPShaderTable* vpShaderTable_, AllPipelineSet* allPipelineSet_)
{
	//一度だけ初期化
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		resourceContainer.Init(textureDataManager_);
		exclusiveDraw = exclusiveDraw_;
		vpShaderTable = vpShaderTable_;
		allPipelineSet = allPipelineSet_;

		CreatePresetOfPipelines();

		initOnlyOnce = false;
	}

}

void M::LogM(std::string message_)
{
	Log(WinApp::log, message_);
}

void M::CreatePresetOfPipelines()
{
	CreateMobilePrimitiveMeshPipeline();
	//CreateTestParticle2DPipeline();
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
		static D3D12_DESCRIPTOR_RANGE descriptorRange2[1] = {};

		RootSignatureCreator::SetDescriptorRange(&descriptorRange[0],
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			0);

		RootSignatureCreator::SetDescriptorRange(&descriptorRange2[0],
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			1);

		meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
			descriptorRange,
			D3D12_SHADER_VISIBILITY_VERTEX,
			1));

		//テクスチャ
		meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
			descriptorRange2,
			D3D12_SHADER_VISIBILITY_PIXEL,
			1));

		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(0));

		return meters;
		};

	CreateNewPipelineSet("TestParticle2D.VS", "TestParticle2D.PS", inputLayOutFunc, rootparameterFunc);
}