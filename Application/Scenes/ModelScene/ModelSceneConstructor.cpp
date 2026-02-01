#include "ModelScene.h"

ModelScene::ModelScene()
{

}

void ModelScene::Instantiate()
{

}

void ModelScene::Init()
{
	Load();

	M::GetInstance()->ChangePostEffect(PostEffectType::kSimpleNeonLike);
	p.Init();
	gm.Init();
	playerAllyModel.Init(nullptr);
	playerTowerModel.Init(nullptr);
	enemyTowerModel.Init(nullptr);
	enemyFactoryModel.Init(nullptr);
	enemyModel.Init(nullptr);
	tenkyu.Init(nullptr);
	playerAllyModel.Init(nullptr);
	gameObjManager->RegisterForContainer(&p,&gm);
	playerAllyModel.model->GetAppearance(0)->trans.pos.x += 1.5f;
	enemyModel.models[0]->GetAppearance(0)->trans.pos.x = -1.5f;

	playerTowerModel.model->GetAppearance(0)->trans.pos = { -5.5,1.5f,1.0f };
	enemyTowerModel.model->GetAppearance(0)->trans.pos = { 5.5,1.5f,1.0f };
	//enemyFactoryModel.model->GetAppearance(0)->trans.pos = { 5.5,0,5.0 };

	Load();
}
