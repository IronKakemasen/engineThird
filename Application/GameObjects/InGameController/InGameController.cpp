#include "InGameController.h"
#include "GameObjectManager.h"
#include "../../GameObjects/Player/Player.h"

void InGameController::ModeData::Set(float time_)
{
	time = time_;
}

float* InGameController::GetCnt()
{
	return &curCnt;
}

void InGameController::SetModeData()
{
	actors[Mode::kEnter].reset(new actor::Enter);
	actors[Mode::kPlayable].reset(new actor::Playable);
	actors[Mode::kUnPlayable].reset(new actor::UnPlayable);
	actors[Mode::kResult].reset(new actor::Result);
	actors[Mode::kGameOver].reset(new actor::GameOver);

	modeData[Mode::kEnter].Set(1.0f);
	modeData[Mode::kPlayable].Set(1.0f);
	modeData[Mode::kUnPlayable].Set(1.0f);
	modeData[Mode::kResult].Set(1.0f);
	modeData[Mode::kGameOver].Set(1.0f);

	int i = 0;
	for (auto& actor : actors)
	{
		actor.second->Init(this, modeData[i].time);
		i++;
	}

}

//コリジョンバックテーブルを設定
void InGameController::SetCollisionBackTable()
{

}

void InGameController::Update()
{
	(*actors[curMode].get())();
}

std::string InGameController::WathchInString()
{
	std::string modeName[Mode::kCount]
	{
		"Enter",
		"Playable",
		"UnPlayable",
		"Result",
		"GameOver"
	};

	return modeName[(int)curMode];
}

void InGameController::Init()
{

	//プレイヤーの挿入
	std::vector<GameObject*> objContainer = gameObjectManager->Find(Tag::kPlayer);
	player = reinterpret_cast<Player*>(objContainer[0]);

	SetIdentity(Tag::kNone);

	SetModeData();

	//位置
	trans.pos.z = 4.0f;
}

void InGameController::Reset()
{

}

void InGameController::Draw(Matrix4* vpMat_)
{

}


InGameController::InGameController()
{

}
