#pragma once
#include "../Transform/Transform.h"
#include "../UVTransform/UVTransform.h"
#include "../../M.h"
#include "../../lowerLayer/engineCore/meshStructure/vertexData/VertexData.h"
#include "../../lowerLayer/engineCore/CommonDrawingSystem/CommonDrawSystem.h"

struct MobileBehavior:CommonDrawingSystem
{
	Transform trans;
	UVTransform uvTrans;
	DrawMode drawMode;

	MobileBehavior();
};

