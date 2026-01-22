#include "Actor.h"
#include "InGameController.h"

void actor::ActorBehavior::Init(InGameController* ing_, float time_)
{
	ing = ing_;
	cnt.Initialize(time_);

}

void actor::Playable::operator()()
{

}

void actor::Playable::Reset()
{
	cnt.count = 0.0f;

}

void actor::Enter::operator()()
{
	if (cnt.IsEnd())
	{
		Reset();
		ing->curMode = InGameController::Mode::kPlayable;
	}
}

void actor::Enter::Reset()
{
	cnt.count = 0.0f;

}

void actor::GameOver ::operator()()
{

}

void actor::GameOver::Reset()
{
	cnt.count = 0.0f;

}

void actor::UnPlayable ::operator()()
{

}

void actor::UnPlayable::Reset()
{
	cnt.count = 0.0f;

}

void actor::Result::operator()()
{

}

void actor::Result::Reset()
{
	cnt.count = 0.0f;

}

