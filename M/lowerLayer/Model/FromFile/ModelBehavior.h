#pragma once
#include "../../M.h"
#include "../../../lowerLayer/engineCore/Mesh/meshStructure/Vertex/Vertex.h"
#include "../../../lowerLayer/engineCore/Render/Appearance/Appearance.h"
#include "../../../lowerLayer/engineCore/Mesh/allMesh/MeshForModel/ModelSimple/ModelSimple.h"

struct ModelBehavior
{
	std::unique_ptr<ModelSimple> model;

	virtual void Update() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;

	ModelBehavior();
};

