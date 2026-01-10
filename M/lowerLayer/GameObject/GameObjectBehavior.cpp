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
	collisionActivate = bool_;
}

bool GameObjectBehavior::IsCollisionActivated()
{
	return collisionActivate;
}

bool GameObjectBehavior::UpdateCollisionBack()
{
	for (auto& [key, value] : collisionBackActivationMap)
	{
		if (!value.func) continue;

		if (value.isActive)
		{
			value.isActive = value.func();
			return true;
		}
	}

	return false;
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
	return rect.get();;
}

bool GameObjectBehavior::HasCollider()
{
	if (rect) return true;

	return false;
}

void GameObjectBehavior::SetRectCollision(float width_, float height_ , Vector3 centerPos_)
{
	if (!rect) rect.reset(new Rect);

	rect->SetShape(width_, height_, centerPos_);
}

void GameObjectBehavior::ActivateOnTriggerEnter(GameObjectBehavior::Tag tag_)
{
	if (collisionBackActivationMap[tag_].func)
	{
		collisionBackActivationMap[tag_].isActive = true;
	}
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
	colObj.emplace_back(obj_);
}

std::vector<GameObjectBehavior*>* GameObjectBehavior::Getter_ColObj()
{
	return &colObj;
}