#pragma once
#include "Transform.h"
struct MainCamera;

namespace CameraActions
{
	class ActionBehavior
	{

	public:
		MainCamera* camera = nullptr;
		static inline Vector3 const kPlayableDefaultLookDir =
			{ 0,-0.85f,0.35f };

		virtual void operator()() = 0;
		virtual void Reset() = 0;
		void Init(MainCamera* camera_);
	};

	struct Action : public ActionBehavior
	{
		virtual void operator()()override {};
		virtual void Reset()override {};
	};

	class FollowPlayer : public Action
	{
		Vector3 offsetFollow = { 0,10,-2.5f };
		Vector3 offsetBeyond;
		Vector3 offsetDebug;
		float const kDefaultFollowCoe = 0.02f;

	public:
		virtual void operator()()override;
		virtual void Reset()override;
	};

	class Enter : public Action
	{

	public:
		virtual void operator()()override;
		virtual void Reset()override;
	};

	class Result : public Action
	{
		Vector3 offsetFollow = { 0,10,-1 };
		float const kDefaultFollowCoe = 0.02f;

	public:
		virtual void operator()()override;
		virtual void Reset()override;
	};

	class GameOver : public Action
	{

	public:
		virtual void operator()()override;
		virtual void Reset()override;
	};

	class UnPlayable : public Action
	{

	public:
		virtual void operator()()override;
		virtual void Reset()override;
	};


};

