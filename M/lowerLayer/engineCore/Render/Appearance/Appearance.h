#pragma once
#include "../../../../utilities/UVTransform/UVTransform.h"
#include "../../../../utilities/Transform/Transform.h"
#include "../../PSO/pipelineCreators/pipelineComponents.h"

struct Appearance
{
	Transform trans;
	UVTransform uvTrans;
	Vector4 color;
	CullMode cullMode;
	BlendMode blendMode;
	int shaderSetIndex;
	int texHandle;
	bool doDraw;

	Appearance();
};

