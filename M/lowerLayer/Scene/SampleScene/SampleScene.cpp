#include "SampleScene.h"

void SampleScene::Update()
{
	mainCamera->Update();
	triangle->Update();

}

void SampleScene::Draw()
{
	Matrix4* vpMat = &mainCamera->vpMat;



	drawExecutor->DrawRegistered(vpMat);
}

void SampleScene::Reset()
{

}

void SampleScene::Debug()
{

}

