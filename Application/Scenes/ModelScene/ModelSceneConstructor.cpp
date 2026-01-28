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

	gameObjManager->RegisterForContainer(&p,&gm);

	enemyModel.models[0]->Getter_Appearance(0)->trans.pos.x = -1.5f;

	Load();
}
