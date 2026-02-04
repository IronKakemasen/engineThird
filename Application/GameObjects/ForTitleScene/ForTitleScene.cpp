#include "ForTitleScene.h"

void ForTitleScene::Update()
{
	player->Update(2);

	for (int i = 0; i < 4; ++i)
	{
		alliance[i]->Update(i%2);
	}

}

void ForTitleScene::Init()
{
	tenkyuu->Init(nullptr);
	player->Init(nullptr);
	player->models[0]->GetAppearance(0)->trans.pos = { 0,0,20 };

	groundPlane->Init(nullptr);
	for (int i = 0; i < 4; ++i)
	{
		alliance[i]->Init(nullptr);
		auto* a = alliance[i].get();
		a->model->GetAppearance(0)->trans.pos = { -i - 1.0f,0,20 };

	}

}
void ForTitleScene::Reset()
{

}
void ForTitleScene::Draw(Matrix4* vpMat_)
{
	tenkyuu->Draw(vpMat_);
	player->Draw(vpMat_);
	groundPlane->Draw(vpMat_);
	for (int i = 0; i < 4; ++i)
	{
		alliance[i]->Draw(vpMat_);
	}
}
void ForTitleScene::SetCollisionBackTable()
{

}

ForTitleScene::ForTitleScene()
{
	tenkyuu.reset(new Tenkyu);
	player.reset(new PlayerModel);
	groundPlane.reset(new GroundPlane);
	for (int i = 0; i < 4; ++i)
	{
		alliance.emplace_back(std::make_unique<PlayerAllyModel>());
	}
}
