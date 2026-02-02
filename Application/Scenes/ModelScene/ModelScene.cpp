#include "ModelScene.h"
#include "../../../M/lowerLayer/engineCore/Light/RectLight/RectLight.h"

void ModelScene::Update()
{
	AdaptToPostEffect();

	if (M::GetInstance()->IsKeyTriggered(KeyType::B))
	{
		ChangeScene(SceneType::kStageSelect);
	}
}

void ModelScene::AdaptToPostEffect()
{
	auto effectType = M::GetInstance()->WatchEffectType();
	auto* dirPara = dirLight->Getter_Para();

	switch (effectType)
	{
	case PostEffectType::kNone:
	{
		//dirPara->intensity = dirLightIntensityNormal;
		//dirPara->pos = dirLightDir;

		for (auto* m : p.model->models)
		{
			auto* appe = m->GetAppearance(0);
			appe->metalic = metalicCommonNormal;
			appe->roughness = roughnessCommonNormal;
		}

		for (auto* m : enemyModel.models)
		{
			auto* enemyMat = m->GetAppearance(0);
			enemyMat->metalic = metalicCommonNormal;
			enemyMat->roughness = roughnessCommonNormal;
		}

		auto* playerMat = playerAllyModel.model->GetAppearance(0);
		playerMat->metalic = metalicCommonNormal;
		playerMat->roughness = roughnessCommonNormal;

		auto* playerTowerMat = playerTowerModel.model->GetAppearance(0);
		playerTowerMat->metalic = metalicCommonNormal;
		playerTowerMat->roughness = roughnessCommonNormal;

		auto* enemyTowerMat = enemyTowerModel.model->GetAppearance(0);
		enemyTowerMat->metalic = metalicCommonNormal;
		enemyTowerMat->roughness = roughnessCommonNormal;

		//auto* enemyFactoryMat = enemyFactoryModel.model->GetAppearance(0);
		//enemyFactoryMat->metalic = metalicCommonNormal;
		//enemyFactoryMat->roughness = roughnessCommonNormal;

		break;
	}
	case PostEffectType::kGreyScale:
	{
		//dirPara->intensity = dirLightIntensityNormal;
		//dirPara->pos = dirLightDir;

		for (auto* m : p.model->models)
		{
			auto* appe = m->GetAppearance(0);
			appe->metalic = metalicCommonNormal;
			appe->roughness = roughnessCommonNormal;
		}
		for (auto* m : enemyModel.models)
		{
			auto* enemyMat = m->GetAppearance(0);
			enemyMat->metalic = metalicCommonNormal;
			enemyMat->roughness = roughnessCommonNormal;
		}

		auto* playerMat = playerAllyModel.model->GetAppearance(0);
		playerMat->metalic = metalicCommonNormal;
		playerMat->roughness = roughnessCommonNormal;

		auto* playerTowerMat = playerTowerModel.model->GetAppearance(0);
		playerTowerMat->metalic = metalicCommonNormal;
		playerTowerMat->roughness = roughnessCommonNormal;

		auto* enemyTowerMat = enemyTowerModel.model->GetAppearance(0);
		enemyTowerMat->metalic = metalicCommonNormal;
		enemyTowerMat->roughness = roughnessCommonNormal;

		//auto* enemyFactoryMat = enemyFactoryModel.model->GetAppearance(0);
		//enemyFactoryMat->metalic = metalicCommonNormal;
		//enemyFactoryMat->roughness = roughnessCommonNormal;

		break;
	}
	case PostEffectType::kSimpleNeonLike:
	{
		//dirPara->intensity = dirLightIntensityNeon;
		//dirPara->pos = dirLightDir;

		for (auto* m : p.model->models)
		{
			auto* appe = m->GetAppearance(0);
			appe->metalic = metalicCommonNeon;
			appe->roughness = roughnessCommonNeon;
		}

		for (auto* m : enemyModel.models)
		{
			auto* enemyMat = m->GetAppearance(0);
			enemyMat->metalic = metalicCommonNeon;
			enemyMat->roughness = roughnessCommonNeon;
		}

		auto* playerMat = playerAllyModel.model->GetAppearance(0);
		playerMat->metalic = metalicCommonNeon;
		playerMat->roughness = roughnessCommonNeon;

		auto* playerTowerMat = playerTowerModel.model->GetAppearance(0);
		playerTowerMat->metalic = metalicCommonNeon;
		playerTowerMat->roughness = roughnessCommonNeon;

		auto* enemyTowerMat = enemyTowerModel.model->GetAppearance(0);
		enemyTowerMat->metalic = metalicCommonNeon;
		enemyTowerMat->roughness = roughnessCommonNeon;

		//auto* enemyFactoryMat = enemyFactoryModel.model->GetAppearance(0);
		//enemyFactoryMat->metalic = metalicCommonNeon;
		//enemyFactoryMat->roughness = roughnessCommonNeon;

		break;
	}
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
		auto* appe = m->GetAppearance(0);
		ImGui::Text(std::to_string(i * 100).c_str());
		ImGui::DragFloat3(("pos" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.pos),0.1f);
		ImGui::DragFloat3(("rotation" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.rotation), 0.1f);
		ImGui::DragFloat3(("lookDIr" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->trans.lookDir), 0.1f);
		ImGui::DragFloat3(("color" + std::to_string(i)).c_str(),
			reinterpret_cast<float*>(&appe->color), 0.1f);

		++i;
	}

	auto* pp = p.rectLight->Getter_Para();
	ImGui::DragFloat("in", &pp->intensity, 1.0f);
	ImGui::DragFloat("width", &pp->width, 0.1f);
	ImGui::DragFloat("height", &pp->height, 0.1f);
	ImGui::DragFloat3("target", reinterpret_cast<float*>(p.rectLight->GetLookDirection()), 0.1f);

	if (ImGui::Button("Save"))
	{
		p.model->Save();
	}

	ImGui::End();


	ImGui::Begin("Dowa");
	ImGui::DragFloat3(("ground" + std::to_string(i)).c_str(),
		reinterpret_cast<float*>(&gm.model->model->GetAppearance(0)->trans.pos), 0.1f);

	ImGui::End();

	ImGui::Begin("CommonParameters");
	ImGui::DragFloat("dirLightIntensityNormal", &dirLightIntensityNormal, 0.1f);
	ImGui::DragFloat("dirLightIntensityNeon", &dirLightIntensityNeon, 0.1f);
	ImGui::DragFloat3("dirLightDir", reinterpret_cast<float*>(&dirLightDir), 0.1f);
	ImGui::SliderFloat("metalicCommonNormal", &metalicCommonNormal, 0.0f,1.0f);
	ImGui::SliderFloat("roughnessCommonNormal", &roughnessCommonNormal, 0.0f, 1.0f);
	ImGui::SliderFloat("metalicCommonNeon", &metalicCommonNeon, 0.0f, 1.0f);
	ImGui::SliderFloat("roughnessCommonNeon", &roughnessCommonNeon, 0.0f, 1.0f);
	if (ImGui::Button("Save"))
	{
		Save();
	}
	ImGui::End();


#endif // USE_IMGUI

}

