#pragma once
#include "../MobileTriangleBehavior.h"

struct TriangleM:MobileTrianglebehavior
{
	virtual void Update()override;
	virtual void Draw(Matrix4& vpMat_)override;

};

