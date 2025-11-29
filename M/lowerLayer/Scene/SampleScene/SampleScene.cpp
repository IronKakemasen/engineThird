#include "SampleScene.h"

void SampleScene::Update()
{
	mainCamera->Update();
	triangle->Update();

}

void SampleScene::Draw()
{
	Matrix4* vpMat = &mainCamera->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);


	particles->Draw(vpMat);
	//drawExecutor->DrawRegistered(vpMat);
}

void SampleScene::Reset()
{

}

void SampleScene::Debug()
{

}

