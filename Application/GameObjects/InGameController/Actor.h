#pragma once
#include "../../../M/utilities/Counter/Counter.h"

struct InGameController;

namespace actor
{
	struct ActorBehavior
	{
		virtual void operator()() = 0;
		virtual void Reset() = 0;
		void Init(InGameController* ing_, float time_);

	protected:
		Counter cnt;
		InGameController* ing = nullptr;
	};

	struct Actor : ActorBehavior
	{
		virtual void operator()() {};
		virtual void Reset() {};
	};

	struct Enter :public Actor
	{
		virtual void operator()()override;
		virtual void Reset()override;
	};

	struct Playable :public Actor
	{
		virtual void operator()()override;
		virtual void Reset()override;
	};

	struct UnPlayable :public Actor
	{
		virtual void operator()()override;
		virtual void Reset()override;
	};

	struct Result :public Actor
	{
		virtual void operator()()override;
		virtual void Reset()override;
	};

	struct GameOver :public Actor
	{
		virtual void operator()()override;
		virtual void Reset()override;
	};

};


