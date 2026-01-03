#include "TitleScene.h"

void TitleScene::Update()
{
	cameraController->Update();

}

void TitleScene::Draw()
{
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void TitleScene::Reset()
{

}

void TitleScene::Debug()
{

}


TitleScene::TitleScene()
{
	Instantiate();
	Init();
}

void TitleScene::Instantiate()
{

}

void TitleScene::Init()
{

}
