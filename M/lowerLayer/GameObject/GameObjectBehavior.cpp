#include "GameObjectBehavior.h"

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

void GameObjectBehavior::UpdateCollisionBack()
{
	for (auto& [key, value] : collisionBackActivationMap)
	{
		if (!value.func) continue;

		if (value.isActive)
		{
			value.isActive = value.func();
		}
	}

}

GameObjectBehavior::Identity::Identity()
{
	name = "none";
	tag = kNone;
	number = 0;
	collisionAttribute = 0;
	collisionMask = 0;

}

bool GameObjectBehavior::Identity::IsCollisionMaskMatched(Identity* other_)
{
	if ((collisionAttribute & other_->collisionMask) == 0)
	{
		return false;
	}

	return true;
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
	collisionBackActivationMap[tag_].isActive = true;
}

void GameObjectBehavior::SetIdentity(Tag tag_)
{
	int no = identity.number;

	Identity identities[Tag::kCount]
	{
		Identity{ "[" + std::to_string(no) + "] : Player" ,tag_,no,0x0000000f,0x00000fff},
		Identity{ "[" + std::to_string(no) + "] : Normal" ,tag_,no ,0x000000f0,0x00ff000f},
		Identity{ "[" + std::to_string(no) + "] : Black" ,tag_,no ,0x00000f00,0x00ff000f},
		Identity{ "[" + std::to_string(no) + "] : Green" ,tag_,no ,0x0000f000,0x00ff000f},
		Identity{ "[" + std::to_string(no) + "] : BlueArea" ,tag_,no ,0x000f0000,0x00000fff},
		Identity{ "[" + std::to_string(no) + "] : GreenArea" ,tag_,no ,0x00f00000,0x00000fff}
	};

	identity = identities[(int)tag_];
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

void GameObject::SetCollidedObjPtr(GameObject* obj_)
{
	colObj = obj_;
}
