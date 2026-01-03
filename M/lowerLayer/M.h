#pragma once
#include "./engineCore/PSO/pipelineCreators/pipelineComponents.h"
#include "./ResourceContainer/ResourceContainer.h"
#include "../utilities/Transform/Transform.h"
#include "../utilities/UVTransform/UVTransform.h"
#include "./engineCore/Mesh/meshStructure/Vertex/Vertex.h"
#include "./engineCore/Mesh/MeshCreator/MeshCreator.h"
#include "./engineCore/Input/InputInterface/InputInterface.h"

#include <functional>
#include <d3d12.h>

class TextureDataManager;
class ExclusiveDraw;
struct CommonDrawingSystem;
class VPShaderTable;
class AllPipelineSet;
struct MeshAndDataCommon;
class LightManager;
class PointLight;
class CameraParameterSetter;
struct CameraBufferPara;
class DirectionalLight;
class KeyboardKeys;

class M
{
	ResourceContainer resourceContainer;
	ExclusiveDraw* exclusiveDraw = nullptr;
	VPShaderTable* vpShaderTable = nullptr;
	AllPipelineSet* allPipelineSet = nullptr;
	MeshCreator* meshCreator = nullptr;
	LightManager* lightManager = nullptr;
	CameraParameterSetter* cameraParameterSetter = nullptr;
	KeyboardKeys* keyboardKeys = nullptr;

public:
	static M* GetInstance();

	void Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, 
		VPShaderTable* vpShaderTable_, AllPipelineSet* allPipelineSet_, MeshCreator* meshCreator_,
		LightManager* lightManager_, CameraParameterSetter* cameraParameterSetter_,
		KeyboardKeys* keyboardKeys_);

	float GetDeltaTime();
	//入力
	bool IsKeyTriggered(KeyType key_);
	bool IsKeyPressed(KeyType key_);

	//Logを出力
	void LogM(std::string message_);

	//テクスチャのインデックスを得る
	int GetTexIndex(TextureTag tag_);

	//shaderSetのインデックスをストリングで取得
	int GetShaderSetIndexFromFileName(std::string vertexShader_, std::string pixelShader_);

	//モデルの生成
	std::unique_ptr<ModelSimple> CreateModel(std::string filePath_);

	//モデルの描画
	void DrawModel(MeshAndDataCommon* meshAndData_, Matrix4* vpMat_);

	//モバイルトライアングルの描画
	void DrawMTriangle(Vertex& left_, Vertex& top_, Vertex& right_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

	//モバイルクアッドの描画
	void DrawMQuad(Vertex& leftTop_, Vertex& rightTop_, Vertex& rightBottom_, Vertex& leftBottom_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

	void DrawInstancingParticle2D(int numParticles_, Vector4 color_, int texHandle_,
		BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_);

	DirectionalLight* ImportDirLight();
	PointLight* ImportPointLight();

	void SetCameraBufferPara(CameraBufferPara cameraBufferPara_);

private:

	M() = default;
	~M() = default;

	// コピー・ムーブ禁止
	M(const M&) = delete;
	M& operator=(const M&) = delete;

};

