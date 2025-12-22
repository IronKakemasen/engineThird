#include "SampleScene.h"
#include "../../../../external/imgui/imgui.h"


void SampleScene::Update()
{
	mainCamera->Update();

	sPlayer->Update();


}

void SampleScene::Draw()
{
	Matrix4* vpMat = &mainCamera->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	sPlayer->Draw(vpMat);

}

void SampleScene::Reset()
{

}

void SampleScene::Debug()
{

}

