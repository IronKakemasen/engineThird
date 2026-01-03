#include "M.h"
#include "./engineCore/Render/ExclusiveDraw/ExclusiveDraw.h"
#include "./engineCore/WinApp.h"
#include "./engineCore/VpShader/vpShaderTable/vpShaderTable.h"
#include "./engineCore/PSO/allPipelineSet.h"
#include "./engineCore/Light/LightManager/LightManager.h"
#include "./engineCore/Buffer/constantBuffer/CameraParaBuffer/CameraParameterSetter/CameraParameterSetter.h"

float M::GetDeltaTime()
{
	return 0.0166666666f;
}

bool M::IsKeyTriggered(KeyType key_)
{
	return keyboardKeys->IsKeyTrigger(key_);
}

bool M::IsKeyPressed(KeyType key_)
{
	return keyboardKeys->IsKeyPress(key_);
}

void M::SetCameraBufferPara(CameraBufferPara CameraBufferPara_)
{
	cameraParameterSetter->SetCameraPara(CameraBufferPara_);
}

DirectionalLight* M::ImportDirLight()
{
	return lightManager->ExportDirectionalLight();
}

PointLight* M::ImportPointLight()
{
	return lightManager->ExportPointLight();

}


std::unique_ptr<ModelSimple> M::CreateModel(std::string filePath_)
{
	return std::move(meshCreator->CreateModel(filePath_));
}

void M::DrawModel(MeshAndDataCommon* meshAndData_, Matrix4* vpMat_)
{
	exclusiveDraw->DrawModel(meshAndData_, vpMat_);
}

void M::DrawInstancingParticle2D(int numParticles_, Vector4 color_, int texHandle_,
	BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
	std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_)
{
	exclusiveDraw->DrawInstancingParticle2D(numParticles_, color_, texHandle_,
		blendMode_, cullMode_, shaderSet_,
		trans_, uvTrans_, vpMat_);
}

void M::DrawMTriangle(Vertex& left_, Vertex& top_, Vertex& right_,
	Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_,int shaderSet_,
	Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_)
{
	exclusiveDraw->DrawMobileTriangle(left_, top_, right_,
		color_, texHandle_, drawMode_, blendMode_, cullMode_, shaderSet_,
		trans_, uvTrans_, vpMat_);
}

void M::DrawMQuad(Vertex& leftTop_, Vertex& rightTop_, Vertex& rightBottom_, Vertex& leftBottom_,
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

void M::Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, 
	VPShaderTable* vpShaderTable_, AllPipelineSet* allPipelineSet_, MeshCreator* meshCreator_,
	LightManager* lightManager_, CameraParameterSetter* cameraParameterSetter_,
	KeyboardKeys* keyboardKeys_)
{
	//一度だけ初期化
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		resourceContainer.Init(textureDataManager_);
		exclusiveDraw = exclusiveDraw_;
		vpShaderTable = vpShaderTable_;
		allPipelineSet = allPipelineSet_;
		meshCreator = meshCreator_;
		lightManager = lightManager_;
		cameraParameterSetter = cameraParameterSetter_;
		keyboardKeys = keyboardKeys_;
		initOnlyOnce = false;
	}
}

void M::LogM(std::string message_)
{
	Log(WinApp::log, message_);
}

