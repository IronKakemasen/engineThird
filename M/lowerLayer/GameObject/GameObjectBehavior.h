#pragma once
#include "../../utilities/Transform/Transform.h"


struct Collider;

struct GameObjectBehavior
{
	enum class ObjectStatus
	{
		kActive,
		kInActive,
	};

	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;

protected:

	ObjectStatus status = ObjectStatus::kActive;
	Transform trans;
	int id;
	Collider* collider = nullptr;

};

struct GameObject:GameObjectBehavior
{
	virtual void Update()override {};
	virtual void Init() override {};
	virtual void Reset() override {};
	virtual void Draw(Matrix4* vpMat_)override {};

	inline auto* Getter_Trans()
	{
		return &trans;
	}

	inline ObjectStatus GetStatus()
	{
		return status;
	}

};

