#pragma once
#include "./engineCore/allPipelineSet/pipelineSet/pipelineCreators/pipelineComponents.h"
#include "./ResourceContainer/ResourceContainer.h"
#include "../utilities/Transform/Transform.h"
#include "../utilities/UVTransform/UVTransform.h"
#include "./engineCore/meshStructure/vertexData/VertexData.h"
#include <functional>
#include <d3d12.h>

class TextureDataManager;
class ExclusiveDraw;
class DrawExecutor;
struct CommonDrawingSystem;
class VPShaderTable;
class AllPipelineSet;

class M
{
	ResourceContainer resourceContainer;
	ExclusiveDraw* exclusiveDraw = nullptr;
	VPShaderTable* vpShaderTable = nullptr;
	AllPipelineSet* allPipelineSet = nullptr;

public:
	static M* GetInstance();

	void Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_, VPShaderTable* vpShaderTable_, AllPipelineSet* allPipelineSet_);

	//Logを出力
	void LogM(std::string message_);

	//テクスチャのインデックスを得る
	int GetTexIndex(TextureTag tag_);

	//shaderSetのインデックスをストリングで取得
	int GetShaderSetIndexFromFileName(std::string vertexShader_, std::string pixelShader_);

	//モバイルトライアングルの描画
	void DrawMTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

	//モバイルクアッドの描画
	void DrawMQuad(VertexData& leftTop_, VertexData& rightTop_, VertexData& rightBottom_, VertexData& leftBottom_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

	//パイプラインセットの生成
	void CreateNewPipelineSet(std::string vsFileName_,
		std::string psFileName_,
		std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> inputElementDescCreateFunc_,
		std::function<std::vector<D3D12_ROOT_PARAMETER>()> rootParameterCreateFunc_);

	void DrawInstancingParticle2D(int numParticles_, Vector4 color_, int texHandle_,
		BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_);


private:

	//俺が作った既存のパイプラインを生成
	void CreatePresetOfPipelines();
	void CreateMobilePrimitiveMeshPipeline();
	void CreateTestParticle2DPipeline();

	M() = default;
	~M() = default;

	// コピー・ムーブ禁止
	M(const M&) = delete;
	M& operator=(const M&) = delete;

};

