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

		initOnlyOnce = false;
	}

}

void M::LogM(std::string message_)
{
	Log(WinApp::log, message_);
}

