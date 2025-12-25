#include "SampleScene.h"
#include "../../../../external/imgui/imgui.h"


void SampleScene::Update()
{
	mainCamera->Update();

	sPlayer->Update();
	sObj->Update();

	ImGui::Begin("oh");
	ImGui::DragFloat3("trans", reinterpret_cast<float*>(&sObj->Getter_Trans()->translate));
	ImGui::End();

}

void SampleScene::Draw()
{
	Matrix4* vpMat = &mainCamera->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	sPlayer->Draw(vpMat);
	sObj->Draw(vpMat);
}

void SampleScene::Reset()
{

}

void SampleScene::Debug()
{

}

