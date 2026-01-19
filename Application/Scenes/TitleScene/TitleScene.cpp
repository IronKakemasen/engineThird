#include "TitleScene.h"

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void TitleScene::Reset()
{

}

void TitleScene::Debug()
{
#ifdef USE_IMGUI



#endif // USE_IMGUI

}

