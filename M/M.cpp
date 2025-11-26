#include "M.h"
#include "./lowerLayer/engineCore/ExclusiveDraw/ExclusiveDraw.h"
#include "./lowerLayer/engineCore/CommonDrawingSystem/CommonDrawSystem.h"
#include "./lowerLayer/engineCore/WinApp.h"
#include "./lowerLayer/engineCore/allShaderData/vpShaderTable/vpShaderTable.h"


void M::DrawMTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_,int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	exclusiveDraw->DrawMobileTriangle(left_, top_, right_,
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
	return vpShaderTable->GetIDFromTableName(vertexShader_ + pixelShader_);
}


void M::Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, VPShaderTable* vpShaderTable_)
{
	//一度だけ初期化
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		resourceContainer.Init(textureDataManager_);
		exclusiveDraw = exclusiveDraw_;
		vpShaderTable = vpShaderTable_;
		initOnlyOnce = false;
	}

}

void M::LogM(std::string message_)
{
	Log(WinApp::log, message_);
}
