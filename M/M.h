#pragma once
#include "./lowerLayer/engineCore/allPipelineSet/pipelineSet/pipelineCreators/pipelineComponents.h"
#include "./lowerLayer/ResourceContainer/ResourceContainer.h"
#include "./utilities/Transform/Transform.h"
#include "./utilities/UVTransform/UVTransform.h"
#include "./lowerLayer/engineCore/meshStructure/vertexData/VertexData.h"
#include "./lowerLayer/engineCore/ExclusiveDraw/ExclusiveDraw.h"

class TextureDataManager;
class ExclusiveDraw;


class M
{
	//一度だけ初期化
	bool initOnlyOnce = true;
	ResourceContainer resourceContainer;
	ExclusiveDraw* exclusiveDraw = nullptr;
public:
	static M* GetInstance();
	void Init(TextureDataManager* textureDataManager_, ExclusiveDraw* exclusiveDraw_);

	//テクスチャのインデックスを得る
	int GetTexIndex(TextureTag tag_);
	void DrawMTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

private:

	M() = default;
	~M() = default;

	// コピー・ムーブ禁止
	M(const M&) = delete;
	M& operator=(const M&) = delete;

};

