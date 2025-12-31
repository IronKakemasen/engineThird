#include "SampleScene.h"
#include "../../../../external/imgui/imgui.h"
#include "../../engineCore/Light/DirectionalLight/DirectionalLight.h"
#include "../../engineCore/Light/PointLight/PointLight.h"


void SampleScene::Update()
{
	cameraController->Update();
	mainCamera->Update();
	
	sPlayer->Update();
	sObj->Update();
}

void SampleScene::Draw()
{
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
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
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&sObj->Getter_Trans()->pos), 0.1f);
		ImGui::DragFloat3("rotate", reinterpret_cast<float*>(&sObj->Getter_Trans()->rotation), 0.1f);
		ImGui::DragFloat3("scale", reinterpret_cast<float*>(&sObj->Getter_Trans()->scale), 0.1f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("camera"))
	{
		ImGui::DragFloat3("pos", reinterpret_cast<float*>(&mainCamera->Getter_Trans()->pos),0.1f);
		ImGui::DragFloat3("tragerDir", reinterpret_cast<float*>(&mainCamera->Getter_Trans()->quaternion.axis),0.025f);
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

}

