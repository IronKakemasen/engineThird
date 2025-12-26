#include "SampleScene.h"
#include "../../../../external/imgui/imgui.h"


void SampleScene::Update()
{
	mainCamera->Update();

	sPlayer->Update();
	sObj->Update();


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
	ImGui::Begin("oh");

	if (ImGui::TreeNode("obj"))
	{
		ImGui::DragFloat3("trans", reinterpret_cast<float*>(&sObj->Getter_Trans()->pos), 0.1f);
		ImGui::DragFloat3("rotate", reinterpret_cast<float*>(&sObj->Getter_Trans()->rotation), 0.1f);
		ImGui::DragFloat3("scale", reinterpret_cast<float*>(&sObj->Getter_Trans()->scale), 0.1f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("camera"))
	{
		ImGui::DragFloat3("trans", reinterpret_cast<float*>(&mainCamera->Getter_Trans()->pos),0.1f);
		ImGui::DragFloat3("tragerDir", reinterpret_cast<float*>(&mainCamera->Getter_Trans()->quaternion.axis),0.025f);
		ImGui::TreePop();
	}
	ImGui::End();

}

