#include "SampleScene.h"
#include "../../../../external/imgui/imgui.h"


void SampleScene::Update()
{
	mainCamera->Update();
	triangle->Update();

}

void SampleScene::Draw()
{
	Matrix4* vpMat = &mainCamera->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);


	//particles->Draw(vpMat);
	//drawExecutor->DrawRegistered(vpMat);
}

void SampleScene::Reset()
{

}

void SampleScene::Debug()
{
	Matrix4 kadai = GetRotateAxisMat({ 1.0f,1.0f,1.0f }, 0.44f);

	ImGui::Begin("kadai");

	for (int i = 0; i < 4; ++i)
	{
		ImGui::DragFloat4(std::to_string(i).c_str(), reinterpret_cast<float*>(&kadai.m[i]));
	}

	ImGui::End();

}

