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

	gameObjManager->RegisterForContainer(&p,&gm);

}
