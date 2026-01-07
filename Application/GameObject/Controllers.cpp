#include "Controllers.h"
#include "InGameController.h"
#include "../../M/lowerLayer/M.h"
#include "BlockManager.h"
#include "NormalBlock.h"

void GameController::Enter::operator()(InGameController* ingC_)
{
	BlockManager::numFall = 0;
	ingC_->cur_cnt = cnt.count;
	

	cnt.Add(M::GetInstance()->GetDeltaTime());
	if (cnt.count <= 0.25f)
	{
	}


	if (cnt.IsEnd())
	{
		ingC_->cur_phase = 0;
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
	if (ingC_->canChangeMode)
	{
		if (InGameController::cur_phase < 1)
		{
			InGameController::cur_phase++;

			BlockManager::doGenerate = true;
		}
		else
		{
			InGameController::cur_phase = 0;
			InGameController::cur_wave++;
			if (Benri::Max(InGameController::cur_wave, 1))
			{
				InGameController::mode =
					InGameController::Mode::kClear;
			}
			else
			{
				InGameController::mode =
					InGameController::Mode::kEnter;
				BlockManager::doGenerate = true;
				BlockManager::mapLast = 0;
			}
		}

		ingC_->canChangeMode = false;
	}
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
		BlockManager::doGenerate = true;
		BlockManager::mapLast = 0;

		ingC_->cur_wave = 0;
		ingC_->cur_phase = 0;
		ingC_->mode = ingC_->kEnter;
		for (auto* block : BlockManager::additions)
		{
			block->SetStatus(GameObjectBehavior::Status::kInActive);
			block->Getter_Trans()->pos = {};
		}
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
		BlockManager::doGenerate = true;
		BlockManager::mapLast = 0;

		ingC_->cur_wave = 0;
		ingC_->cur_phase = 0;
		ingC_->mode = ingC_->kEnter;
		for (auto* block : BlockManager::additions)
		{
			block->SetStatus(GameObjectBehavior::Status::kInActive);
			block->Getter_Trans()->pos = {};
		}

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
		Reset();
	}

}

void GameController::Result::Reset()
{
	cnt.Initialize(time);
}
