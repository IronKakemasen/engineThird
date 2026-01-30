#pragma once
#include "ModelBehavior.h"


class PlayerAllyModel :public ModelBehavior
{
	void MoveAnim(int animPattern_);
	Counter moveAnimCnt;
	int pyonNum = 0;
	int pyonPattern = 0;
	int animPattern = 0;


public:
	PlayerAllyModel();
	virtual void Update()override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void Init(Transform* gameObjectTrans_)override;
	virtual void Reset()override;

};

