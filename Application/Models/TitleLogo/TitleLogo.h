#pragma once
#include "ModelBehavior.h"


class TitleLogo :public ModelBehavior
{
	std::vector<std::unique_ptr<ModelSimple>> L2;
	std::vector<std::unique_ptr<ModelSimple>> O2;
	std::vector<ModelSimple*> models;

public:

	TitleLogo();
	virtual void Update(int mode_ = 0, float count_ = 0.0f)override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

