#include "Controllers.h"
#include "InGameController.h"
#include "../../M/lowerLayer/M.h"

void GameController::Enter::operator()(InGameController* ingC_)
{
	ingC_->cur_cnt = cnt.count;

	cnt.Add(M::GetInstance()->GetDeltaTime());

	if (cnt.IsEnd())
	{
		ingC_->cur_wave = 0;
		ingC_->mode = ingC_->kPlayable;
		Reset();
	}
}

void GameController::Enter::Reset()
{
	cnt.Initialize(time);
}

void GameController::Playable::operator()(InGameController* ingC_)
{

}

void GameController::Playable::Reset()
{
	cnt.Initialize(time);
}

void GameController::Death::operator()(InGameController* ingC_)
{
	ingC_->cur_cnt = cnt.count;

	cnt.Add(M::GetInstance()->GetDeltaTime());

	if (cnt.IsEnd())
	{
		ingC_->cur_wave = 0;
		ingC_->mode = ingC_->kEnter;
		Reset();
	}

}

void GameController::Death::Reset()
{
	cnt.Initialize(time);
}

void GameController::Clear::operator()(InGameController* ingC_)
{
	ingC_->cur_cnt = cnt.count;

	cnt.Add(M::GetInstance()->GetDeltaTime());

	if (cnt.IsEnd())
	{
		ingC_->cur_wave = 0;
		ingC_->mode = ingC_->kEnter;
		Reset();
	}

}

void GameController::Clear::Reset()
{
	cnt.Initialize(time);
}

void GameController::Result::operator()(InGameController* ingC_)
{
	ingC_->cur_cnt = cnt.count;

	cnt.Add(M::GetInstance()->GetDeltaTime());

	if (cnt.IsEnd())
	{
		ingC_->cur_wave = 0;
		ingC_->mode = ingC_->kEnter;
		Reset();
	}

}

void GameController::Result::Reset()
{
	cnt.Initialize(time);
}
