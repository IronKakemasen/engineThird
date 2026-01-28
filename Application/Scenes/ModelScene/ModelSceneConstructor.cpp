#include "ModelScene.h"

ModelScene::ModelScene()
{

}

void ModelScene::Instantiate()
{

}

void ModelScene::Init()
{
	M::GetInstance()->ChangePostEffect(PostEffectType::kNone);
	p.Init();
	gm.Init();

	enemyModel.Init(nullptr);
	tenkyu.Init(nullptr);
	enemyModel.model->Getter_Appearance(0)->trans.pos.x = -1.8f;

	gameObjManager->RegisterForContainer(&p,&gm);

	Load();
}
