#pragma once
#include "../Transform/Transform.h"
#include "../UVTransform/UVTransform.h"
#include "../../M.h"
#include "../../lowerLayer/engineCore/meshStructure/vertexData/VertexData.h"

struct MobileBehavior
{
	Transform trans;
	UVTransform uvTrans;

	Vector4 color;
	CullMode cullMode;
	DrawMode drawMode;
	BlendMode blendMode;
	int texHandle;

	MobileBehavior();
};

