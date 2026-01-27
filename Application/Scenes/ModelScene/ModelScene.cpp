#include "ModelScene.h"

void ModelScene::Update()
{
	AdaptToPostEffect();
}

void ModelScene::AdaptToPostEffect()
{
	auto effectType = M::GetInstance()->WatchEffectType();
	auto* dirPara = dirLight->Getter_Para();

	switch (effectType)
	{
	case PostEffectType::kNone:
		dirPara->intensity = 1.0f;

		break;

	case PostEffectType::kGreyScale:
		dirPara->intensity = 1.0f;

		break;

	case PostEffectType::kSimpleNeonLike:
		dirPara->intensity = 12.0f;

		break;
	}
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

void ModelScene::Save()
{
	std::string key = "/ID/";
	Json::SaveParam(path, key + "dirLightIntensityNormal", dirLightIntensityNormal);
	Json::SaveParam(path, key + "dirLightIntensityNeon", dirLightIntensityNeon);
	Json::SaveParam(path, key + "dirLightDir", dirLightDir);
	Json::SaveParam(path, key + "metalicCommonNormal", metalicCommonNormal);
	Json::SaveParam(path, key + "roughnessCommonNormal", roughnessCommonNormal);
	Json::SaveParam(path, key + "metalicCommonNeon", metalicCommonNeon);
	Json::SaveParam(path, key + "roughnessCommonNeon", roughnessCommonNeon);
	Json::Save(path);
}

void ModelScene::Load()
{
	std::string key = "/ID/";
	Json::LoadParam(path, key + "dirLightIntensityNormal", dirLightIntensityNormal);
	Json::LoadParam(path, key + "dirLightIntensityNeon", dirLightIntensityNeon);
	Json::LoadParam(path, key + "dirLightDir", dirLightDir);
	Json::LoadParam(path, key + "metalicCommonNormal", metalicCommonNormal);
	Json::LoadParam(path, key + "roughnessCommonNormal", roughnessCommonNormal);
	Json::LoadParam(path, key + "metalicCommonNeon", metalicCommonNeon);
	Json::LoadParam(path, key + "roughnessCommonNeon", roughnessCommonNeon);
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

