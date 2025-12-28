#pragma once
#include "../../../../utilities/UVTransform/UVTransform.h"
#include "../../../../utilities/Transform/Transform.h"
#include "../../PSO/pipelineCreators/pipelineComponents.h"
#include <unordered_map>

struct Appearance
{
	enum TextureType
	{
		kColormap,
		kNormalmap,


		kNone,
		kCount
	};

	Transform trans;
	UVTransform uvTrans;
	Vector4 color;
	CullMode cullMode;
	BlendMode blendMode;
	int shaderSetIndex;
	std::unordered_map < TextureType ,int > texHandlesContainer;
	std::vector < int > use_texHandles;
	bool doDraw;

	void SetUsingTextureFromContainer(TextureType colorMap_, TextureType normalMap_);

	Appearance();
};

