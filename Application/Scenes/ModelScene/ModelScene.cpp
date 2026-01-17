#include "ModelScene.h"

void ModelScene::Update()
{

}

void ModelScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void ModelScene::Reset()
{

}

void ModelScene::Debug()
{
#ifdef USE_IMGUI



#endif // USE_IMGUI

}

