#pragma once
#include "../../../utilities/vectorAndMatrix/vectorAndMatrix.h"
#include "../allPipelineSet/pipelineSet/pipelineCreators/pipelineComponents.h"

struct CommonDrawingSystem
{
	Vector4 color;
	CullMode cullMode;
	BlendMode blendMode;
	int shaderSetIndex;
	int texHandle;
	bool doDraw;
	int id;

	CommonDrawingSystem();
	virtual void Draw(Matrix4* vpMat_) = 0;
};

