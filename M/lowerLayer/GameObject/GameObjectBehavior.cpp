#include "GameObjectBehavior.h"


//新しくゲームオブジェクトを作ったらテーブルに追加してほしい
void GameObjectBehavior::SetIdentity(Tag tag_)
{
	int no = identity.number;

	Identity identitiesTable[Tag::kCount]
	{
		Identity{ "[" + std::to_string(no) + "] : Shikoutei" ,tag_,no,0x0000000f,0x0000fff0},
	};

	identity = identitiesTable[(int)tag_];
}

std::string GameObjectBehavior::Getter_Name()
{
	return identity.name;
}

void GameObjectBehavior::SwitchCollisionActivation(bool bool_)
{
	collision.collisionActivate = bool_;
}

bool GameObjectBehavior::IsCollisionActivated()
{
	return collision.collisionActivate;
}

GameObjectBehavior::Identity::Identity()
{
	name = "noName";
	tag = kNone;
	number = 0;
	collisionAttribute = 0;
	collisionMask = 0;
}

bool GameObjectBehavior::Identity::IsCollisionMaskMatched(Identity* other_)
{

	return false;
}

GameObjectBehavior::Identity::Identity(std::string name_, Tag tag_, int number_, 
	uint32_t att_, uint32_t mask_)
{
	name = name_;
	tag = tag_;
	number = number_;
	collisionAttribute = att_;
	collisionMask = mask_;
}

bool GameObjectBehavior::IsCollisionMaskMatched(Identity* other_)
{
	return identity.IsCollisionMaskMatched(other_);
}

GameObjectBehavior::Identity* GameObjectBehavior::Getter_Identity()
{
	return &identity;
}

Rect* GameObjectBehavior::Getter_Rect()
{
	return collision.rect.get();;
}

bool GameObjectBehavior::HasRectCollider()
{
	if (collision.rect) return true;

	return false;
}

bool GameObjectBehavior::HasCollider()
{
	int hit = 0;
	if (collision.rect)
	{
		hit++;
	}

	return hit;
}

void GameObjectBehavior::SetRectCollision(float width_, float height_ , Vector3 centerPos_)
{
	if (!collision.rect) collision.rect.reset(new Rect);

	collision.rect->SetShape(width_, height_, centerPos_);
}

void GameObjectBehavior::ActivateOnTriggerEnter(GameObjectBehavior::Tag tag_)
{
	if (!collision.collisionBackActivationMap[tag_].collisionBack) return;

#ifdef _DEBUG
	if (collision.collisionBackActivationMap[tag_].collisionBack())
	{
		forDebug.colorForCollision = { 200,50,50,255 };
	}
	else
	{
		forDebug.colorForCollision = { 50,50,200,255 };
	}
#endif // _DEBUG
#ifndef _DEBUG
	collision.collisionBackActivationMap[tag_].collisionBack();
#endif // _DEBUG
}

void GameObjectBehavior::SetNumber(int number_)
{
	identity.number = number_;
}

void GameObjectBehavior::SetStatus(Status dst_)
{
	status = dst_;
}

GameObject::GameObject()
{
	status = Status::kActive;
}

void GameObjectBehavior::SetCollidedObjPtr(GameObjectBehavior* obj_)
{
	collision.colObj = obj_;
}

GameObjectBehavior* GameObjectBehavior::Getter_ColObj()
{
	return collision.colObj;
}