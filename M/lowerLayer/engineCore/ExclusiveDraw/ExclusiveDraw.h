#pragma once
#include "../../../utilities/Transform/Transform.h"
#include "../../../utilities/UVTransform/UVTransform.h"
#include "../Mesh/meshStructure/vertexData/VertexData.h"
#include "../allPipelineSet/pipelineSet/pipelineCreators/pipelineComponents.h"

class AllPipelineSet;
class AllMesh;
struct ShaderBuffer;

class ExclusiveDraw
{
	AllPipelineSet* allPipelineSet = nullptr;
	AllMesh* allMesh = nullptr;
	std::vector<ShaderBuffer >* shaderBufferData;

public:
	void Init(AllPipelineSet* allPipelineSet_, AllMesh* allMesh_, std::vector<ShaderBuffer >* shaderBufferData_);

	void DrawMobileTriangle(VertexData& left_, VertexData& top_, VertexData& right_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_ ,CullMode cullMode_,int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);

	void DrawMobileQuad(VertexData& leftTop_, VertexData& rightTop_, VertexData& rightBottom_, VertexData& leftBottom_,
		Vector4 color_, int texHandle_, DrawMode drawMode_, BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		Transform& trans_, UVTransform& uvTrans_, Matrix4& vpMat_);
	
	void DrawInstancingParticle2D(int numParticles_, Vector4 color_, int texHandle_,
		BlendMode blendMode_, CullMode cullMode_, int shaderSet_,
		std::vector<Transform> trans_, UVTransform* uvTrans_, Matrix4* vpMat_);


	void ResetDrawIndexes();
};

