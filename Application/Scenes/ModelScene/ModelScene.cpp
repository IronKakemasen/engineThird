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
	ImGui::Begin("PlayerModel");
	int i = 0;
	for (auto* m : p.model->models)
	{
		auto* appe = m->Getter_Appearance(0);
		ImGui::Text(std::to_string(i * 100).c_str());
		ImGui::DragFloat3(("pos" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.pos),0.1f);
		ImGui::DragFloat3(("rotation" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.rotation), 0.1f);
		ImGui::DragFloat3(("lookDIr" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.lookDir), 0.1f);

		++i;
	}

	if (ImGui::Button("Save"))
	{
		p.model->Save();
	}

	ImGui::End();


	ImGui::Begin("ground");
	ImGui::DragFloat3(("pos" + std::to_string(i)).c_str(),
		reinterpret_cast<float*>(&gm.model->model->Getter_Appearance(0)->trans.pos), 0.1f);
	ImGui::End();


#endif // USE_IMGUI

}

