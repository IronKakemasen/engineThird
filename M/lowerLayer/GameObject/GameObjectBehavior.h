#pragma once
#include "../../utilities/Transform/Transform.h"
#include "../../utilities/Counter/Counter.h"
#include <string>

struct Collider;

struct GameObjectBehavior
{
	enum class Status
	{
		kActive,
		kInActive,
	};

	enum Tag
	{
		kPlayer,
		kNormal,
		kBlack,
		kGreen,

		kCount,
		kNone,
	};
private :
	struct Identity
	{
		std::string name;
		Tag tag;
		int number;
		Identity();
		Identity(std::string name_, Tag tag_, int number_);
	};

	Identity identity;

public:
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;
	void SetStatus(Status dst_);
	void SetNumber(int id_);
	void SetIdentity(Tag tag_);
	std::string Getter_Name();
protected:

	Status status;
	Transform trans;
	Collider* collider = nullptr;

};

struct GameObject:public GameObjectBehavior
{
	GameObject();
	virtual void Update()override {};
	virtual void Init() override {};
	virtual void Reset() override {};
	virtual void Draw(Matrix4* vpMat_)override {};

	inline auto* Getter_Trans()
	{
		return &trans;
	}

	inline Status GetStatus()
	{
		return status;
	}

};

