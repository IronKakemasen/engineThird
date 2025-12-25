#pragma once
#include "./engineCore/PSO/pipelineCreators/pipelineComponents.h"
#include "./ResourceContainer/ResourceContainer.h"
#include "../utilities/Transform/Transform.h"
#include "../utilities/UVTransform/UVTransform.h"
#include "./engineCore/Mesh/meshStructure/Vertex/Vertex.h"
#include "./engineCore/Mesh/MeshCreator/MeshCreator.h"

#include <functional>
#include <d3d12.h>

class TextureDataManager;
class ExclusiveDraw;
class DrawExecutor;
struct CommonDrawingSystem;
class VPShaderTable;
class AllPipelineSet;
struct MeshAndDataCommon;


class M
{
	ResourceContainer resourceContainer;
	ExclusiveDraw* exclusiveDraw = nullptr;
	VPShaderTable* vpShaderTable = nullptr;
	AllPipelineSet* allPipelineSet = nullptr;
	MeshCreator* meshCreator = nullptr;

public:
	static M* GetInstance();

	void Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, 
		VPShaderTable* vpShaderTable_, AllPipelineSet* allPipelineSet_, MeshCreator* meshCreator_);

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


private:

	M() = default;
	~M() = default;

	// コピー・ムーブ禁止
	M(const M&) = delete;
	M& operator=(const M&) = delete;

};

