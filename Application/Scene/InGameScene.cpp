#include "InGameScene.h"


void InGameScene::Update()
{
	cameraController->Update();

}

void InGameScene::Draw()
{
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void InGameScene::Reset()
{

}

void InGameScene::Debug()
{

}

