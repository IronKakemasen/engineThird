#pragma once
#include "../../M.h"
#include "../../../lowerLayer/engineCore/Mesh/meshStructure/Vertex/Vertex.h"
#include "../../../lowerLayer/engineCore/Render/Appearance/Appearance.h"
#include "../../../lowerLayer/engineCore/Mesh/allMesh/MeshForModel/ModelSimple/ModelSimple.h"

struct ModelBehavior
{
	std::unique_ptr<ModelSimple> model;

	ModelBehavior();

	virtual void Update() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;
	virtual void Init(Transform* gameObjectTrans_) = 0;
	virtual void Reset() = 0;

	void MakeAllPartsBeChildren(Transform* gameObject_);

};

