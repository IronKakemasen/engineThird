#include "InGameScene.h"


void InGameScene::Update()
{
	cameraController->Update();
	gameObjManager->Update();
}

void InGameScene::Draw()
{
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	gameObjManager->Render(vpMat);

}

void InGameScene::Reset()
{
	gameObjManager->Reset();
}

void InGameScene::Debug()
{

}

