#pragma once
#include "../../../utilities/Transform/Transform.h"
#include "../../../utilities/UVTransform/UVTransform.h"
#include "../../M.h"
#include "../../../lowerLayer/engineCore/Mesh/meshStructure/vertexData/VertexData.h"
#include "../../../lowerLayer/engineCore/CommonDrawingSystem/CommonDrawSystem.h"

struct MobileBehavior:CommonDrawingSystem
{
	Transform trans;
	UVTransform uvTrans;
	DrawMode drawMode;

	MobileBehavior();
};

