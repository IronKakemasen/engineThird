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
#ifdef USE_IMGUI

	gameObjManager->Debug();

	ImGui::Begin("oh");

	if (ImGui::TreeNode("camera"))
	{
		auto* cur_camera = cameraController->GetUsingCamera();
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&cur_camera->Getter_Trans()->pos), 0.1f);
		ImGui::DragFloat3("tragerDir", reinterpret_cast<float*>(&cur_camera->Getter_Trans()->quaternion.axis), 0.025f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("dirLight"))
	{
		auto* para = dirLight->Getter_Para();
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&para->pos), 0.1f);
		ImGui::DragFloat3("color", reinterpret_cast<float*>(&para->color), 0.1f);
		ImGui::DragFloat("intensity", reinterpret_cast<float*>(&para->intensity), 0.025f);
		ImGui::Checkbox("isActive", reinterpret_cast<bool*>(&para->isActive));

		ImGui::TreePop();
	}
	for (int i = 0; i < 3; ++i)
	{
		if (ImGui::TreeNode(std::to_string(i).c_str()))
		{
			auto* para = pointLights[i]->Getter_Para();
			ImGui::DragFloat3("pos", reinterpret_cast<float*>(&para->pos), 0.1f);
			ImGui::DragFloat3("color", reinterpret_cast<float*>(&para->color), 0.1f);
			ImGui::DragFloat("intensity", reinterpret_cast<float*>(&para->intensity), 0.025f);
			ImGui::DragFloat("radius", reinterpret_cast<float*>(&para->invSqrRadius), 1.0f);
			ImGui::Checkbox("isActive", reinterpret_cast<bool*>(&para->isActive));

			ImGui::TreePop();
		}
	}
	ImGui::End();


#endif // USE_IMGUI

}

