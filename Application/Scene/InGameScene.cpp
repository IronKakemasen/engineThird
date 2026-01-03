#include "InGameScene.h"

void InGameScene::Update()
{
	camera.Update();
}

void InGameScene::Draw()
{
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void InGameScene::Reset()
{
	gameObjManager->Reset();
}

void InGameScene::Debug()
{
#ifdef USE_IMGUI

	gameObjManager->Debug();

	static float f = ImGui::GetIO().DeltaTime;
	f = ImGui::GetIO().DeltaTime;

	ImGui::Begin("InGame");
	ImGui::Text(InGameController::CurMode().c_str());
	ImGui::DragFloat("FPS", &f);
	ImGui::DragFloat("cnt", &InGameController::cur_cnt);
	ImGui::End();


	ImGui::Begin("oh");

	if (ImGui::TreeNode("camera"))
	{
		auto* cur_camera = cameraController->GetUsingCamera();
		auto* para = cur_camera->Getter_Parameters();
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&para->trans.pos), 0.1f);
		ImGui::DragFloat3("tragerDir", reinterpret_cast<float*>(&para->trans.lookDir), 0.025f);
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

