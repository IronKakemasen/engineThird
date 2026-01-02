#include "GameObjectBehavior.h"

std::string GameObjectBehavior::Getter_Name()
{
	return identity.name;
}


GameObjectBehavior::Identity::Identity()
{
	name = "none";
	tag = kNone;
	number = 0;
}
GameObjectBehavior::Identity::Identity(std::string name_, Tag tag_, int number_)
{
	name = name_;
	tag = tag_;
	number = number_;
}

void GameObjectBehavior::SetIdentity(Tag tag_)
{
	int no = identity.number;

	Identity identities[Tag::kCount]
	{
		Identity{ "[" + std::to_string(no) + "] : Player" ,tag_,no},
		Identity{ "[" + std::to_string(no) + "] : Normal" ,tag_,no },
		Identity{ "[" + std::to_string(no) + "] : Black" ,tag_,no },
		Identity{ "[" + std::to_string(no) + "] : Green" ,tag_,no }
	};

	identity = identities[(int)tag_];
	//kPlayer,
	//kNormal,
	//kBlack,
	//kGreen,
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
