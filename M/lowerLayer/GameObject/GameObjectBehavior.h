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
	//オブジェクトのステータス
	enum class Status
	{
		kActive,	//更新や描画処理します
		kInActive,	//しません
	};

	//ゲームオブジェクトのタグ。適宜追加
	enum Tag
	{
		kShikoutei,


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
	bool collisionActivate = true;

protected:
	Status status;
	Transform trans;
	std::unique_ptr <Rect> rect;
	//各衝突相手に対して衝突後の処理（バック）を設定するための箱
	std::unordered_map<Tag, CollisionBackSet> collisionBackActivationMap;
	std::vector<GameObjectBehavior*> colObj;

public:
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Draw(Matrix4* vpMat_) = 0;
	virtual void SetCollisionBackTable() = 0;

	void SetStatus(Status dst_);
	void SetIdentity(Tag tag_);
	void SetRectCollision(float width_, float height_, Vector3 centerPos_ = {});
	void SwitchCollisionActivation(bool bool_);



	void SetNumber(int id_);
	void ActivateOnTriggerEnter(Tag tag_);
	bool IsCollisionMaskMatched(Identity* other_);
	Identity* Getter_Identity();
	bool HasCollider();
	std::string Getter_Name();
	bool IsCollisionActivated();
	bool UpdateCollisionBack();
	void SetCollidedObjPtr(GameObjectBehavior* obj_);
	std::vector<GameObjectBehavior*>* Getter_ColObj();
	Rect* Getter_Rect();

};

struct GameObject:public GameObjectBehavior
{

public:

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

