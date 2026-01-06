#pragma once
#include "../../utilities/Transform/Transform.h"
#include "../../utilities/Counter/Counter.h"
#include "../../utilities/Easing/EasingFunctions.h"
#include "../../utilities/ConvertToRadian/ConvertToRadian.h"
#include "../Collision/Shape/Rect.h"
#include <string>
#include <memory>

struct GameObjectBehavior
{
	enum class Status
	{
		kActive,
		kInActive,
	};

	enum class Uwa
	{
		kNotUse,
		kUsing,
		kErase,
		kFall,
	};

	enum Tag
	{
		kPlayer,
		kNormal,
		kBlack,
		kGreen,
		kBlueArea,
		kGreenArea,


		kCount,
		kNone,
	};
private :
	struct Identity
	{
		std::string name;
		Tag tag;
		int number;
		//自身の衝突ナンバー
		uint32_t collisionAttribute;
		//衝突可能相手のナンバー
		uint32_t collisionMask;

		Identity();
		Identity(std::string name_, Tag tag_, int number_, uint32_t att_, uint32_t mask_);
		bool IsCollisionMaskMatched(Identity* other_);

	};

	struct CollisionBackSet
	{
		bool isActive = false;
		std::function<bool()> func;
	};

	Identity identity;
	//各衝突相手に対して衝突後の処理（バック）を設定するための箱
	std::unordered_map<Tag, CollisionBackSet> collisionBackActivationMap;
	bool collisionActivate = false;

public:
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;
	virtual void SetCollisionBackTable() = 0;

	void SetStatus(Status dst_);
	void SetNumber(int id_);
	void SetIdentity(Tag tag_);
	void ActivateOnTriggerEnter(Tag tag_);
	void SetRectCollision(float width_, float height_, Vector3 centerPos_ = {});
	bool IsCollisionMaskMatched(Identity* other_);
	Identity* Getter_Identity();
	Rect* Getter_Rect();
	bool HasCollider();
	std::string Getter_Name();
	void SwitchCollisionActivation(bool bool_);
	bool IsCollisionActivated();
	void UpdateCollisionBack();
protected:

	Status status;
	Transform trans;
	std::unique_ptr <Rect> rect;


};

struct GameObject:public GameObjectBehavior
{
private:
	GameObject* colObj = nullptr;

public:
	Uwa uwa = Uwa::kNotUse;

	GameObject();
	virtual void Update()override {};
	virtual void Init() override {};
	virtual void Reset() override {};
	virtual void Draw(Matrix4* vpMat_)override {};
	void SetCollidedObjPtr(GameObject* obj_);

	inline auto* Getter_Trans()
	{
		return &trans;
	}


	inline Status GetStatus()
	{
		return status;
	}



};

