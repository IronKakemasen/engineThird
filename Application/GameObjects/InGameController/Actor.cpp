#include "Actor.h"
#include "InGameController.h"

void actor::ActorBehavior::Init(InGameController* ing_, float time_)
{
	ing = ing_;
	cnt.Initialize(time_);

}

void actor::Playable::operator()()
{
	ing->curCnt = cnt.count;

	cnt.Add();
}

void actor::Playable::Reset()
{
	cnt.count = 0.0f;

}

void actor::Enter::operator()()
{
	ing->curCnt = cnt.count;

	if (cnt.IsEnd())
	{
		ing->curMode = InGameController::Mode::kPlayable;
		Reset();

		return;
	}

	cnt.Add();

}

void actor::Enter::Reset()
{
	cnt.count = 0.0f;

}

void actor::GameOver ::operator()()
{
	ing->curCnt = cnt.count;

	if (cnt.IsEnd())
	{
		Reset();
		return;
	}

	cnt.Add();

}

void actor::GameOver::Reset()
{
	cnt.count = 0.0f;

}

void actor::UnPlayable ::operator()()
{
	ing->curCnt = cnt.count;

	cnt.Add();

}

void actor::UnPlayable::Reset()
{
	cnt.count = 0.0f;

}

void actor::Result::operator()()
{
	ing->curCnt = cnt.count;

	if (cnt.IsEnd())
	{
		Reset();
		return;
	}

	cnt.Add();

}

void actor::Result::Reset()
{
	cnt.count = 0.0f;

}

