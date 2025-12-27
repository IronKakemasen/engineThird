#pragma once
#include "../../../../utilities/UVTransform/UVTransform.h"
#include "../../../../utilities/Transform/Transform.h"
#include "../../PSO/pipelineCreators/pipelineComponents.h"

struct Appearance
{
	enum TextureType
	{
		kColormap,
		kNormalmap,


		kCount
	};

	Transform trans;
	UVTransform uvTrans;
	Vector4 color;
	CullMode cullMode;
	BlendMode blendMode;
	int shaderSetIndex;
	std::vector < int > texHandles;

	bool doDraw;

	Appearance();
};

