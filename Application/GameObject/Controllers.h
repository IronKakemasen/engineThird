#pragma once
#include "../../M/utilities/Counter/Counter.h"

struct InGameController;

namespace GameController
{
	struct ControllBehavior
	{
		Counter cnt;
		float time;
		virtual void operator()(InGameController* ingC_) = 0;
		virtual void Reset() = 0;
	};

	struct Enter:ControllBehavior
	{
		virtual void operator()(InGameController* ingC_)override;
		virtual void Reset() override;
		Enter()
		{
			time = 4.0f;
			cnt.Initialize(time);

		}
	};

	struct Playable :ControllBehavior
	{
		virtual void operator()(InGameController* ingC_)override;
		virtual void Reset() override;
		Playable()
		{
			time = 4.0f;
			cnt.Initialize(time);

		}

	};

	struct Death :ControllBehavior
	{
		virtual void operator()(InGameController* ingC_)override;
		virtual void Reset() override;

		Death()
		{
			time = 4.0f;
			cnt.Initialize(time);

		}

	};

	struct Clear :ControllBehavior
	{
		virtual void operator()(InGameController* ingC_)override;
		virtual void Reset() override;
		Clear()
		{
			time = 4.0f;
			cnt.Initialize(time);

		}

	};

	struct Result :ControllBehavior
	{
		virtual void operator()(InGameController* ingC_)override;
		virtual void Reset() override;
		Result()
		{
			time = 4.0f;
			cnt.Initialize(time);

		}

	};

}


