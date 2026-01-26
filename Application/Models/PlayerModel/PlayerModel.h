#pragma once
#include "ModelBehavior.h"


class PlayerModel :public ModelBehavior
{


public:

	std::unique_ptr<ModelSimple> head;
	std::unique_ptr<ModelSimple> body;
	std::unique_ptr<ModelSimple> hand_L;
	std::unique_ptr<ModelSimple> hand_R;
	std::unique_ptr<ModelSimple> leg_L;
	std::unique_ptr<ModelSimple> leg_R;

	std::vector<ModelSimple*> models;

	PlayerModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

