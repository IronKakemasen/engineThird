#include "PlayerModel.h"

void PlayerModel::Save()
{
	std::string key = "/ID/";
	int i = 0;
	for (auto* m : models)
	{
		Json::SaveParam(path, key + "pos" + std::to_string(i),
			m->GetAppearance(0)->trans.pos);
		Json::SaveParam(path, key + "rotation" + std::to_string(i),
			m->GetAppearance(0)->trans.rotation);
		Json::SaveParam(path, key + "lookDir" + std::to_string(i),
			m->GetAppearance(0)->trans.lookDir);
		Json::SaveParam(path, key + "color" + std::to_string(i),
			m->GetAppearance(0)->color);

		++i;
	}

	Json::Save(path);
}

void PlayerModel::Load()
{
	std::string key = "/ID/";
	int i = 0;
	for (auto* m : models)
	{
		Json::LoadParam(path, key + "pos" + std::to_string(i),
			m->GetAppearance(0)->trans.pos);
		Json::LoadParam(path, key + "rotation" + std::to_string(i),
			m->GetAppearance(0)->trans.rotation);
		Json::LoadParam(path, key + "lookDir" + std::to_string(i),
			m->GetAppearance(0)->trans.lookDir);
		Json::LoadParam(path, key + "color" + std::to_string(i),
			m->GetAppearance(0)->color);

		++i;
	}
}

PlayerModel::PlayerModel()
{
	//モデルの生成(必須)
	body = M::GetInstance()->CreateModel(  "./resource/application/Model/Player/P_Body/P_Body.gltf");
	hand_L = M::GetInstance()->CreateModel("./resource/application/Model/Player/P_Hand_L/P_Hand_L.gltf");
	hand_R = M::GetInstance()->CreateModel("./resource/application/Model/Player/P_Hand_R/P_Hand_R.gltf");
	head = M::GetInstance()->CreateModel(  "./resource/application/Model/Player/P_Head/P_Head.gltf");
	leg_L = M::GetInstance()->CreateModel( "./resource/application/Model/Player/P_Leg_L/P_Leg_L.gltf");
	leg_R = M::GetInstance()->CreateModel( "./resource/application/Model/Player/P_Leg_R/P_Leg_R.gltf");

	models.emplace_back(body.get());
	models.emplace_back(hand_L.get());
	models.emplace_back(hand_R.get());
	models.emplace_back(head.get());
	models.emplace_back(leg_L.get());
	models.emplace_back(leg_R.get());

}

void PlayerModel::Update()
{

}

void PlayerModel::Draw(Matrix4* vpMat_)
{
	for (auto* m : models)
	{
		M::GetInstance()->DrawModel(m, vpMat_);

	}
}

void PlayerModel::Init(Transform* gameObjectTrans_)
{
	auto* m = M::GetInstance();

	//ゲームオブジェクトと全モデルのペアレント化
	body->GetAppearance(0)->trans.BeChildren(gameObjectTrans_);
	body->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap]=
		m->GetTexIndex(TextureTag::kPlayerBodyN);

	hand_L->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	hand_L->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHandN);

	hand_R->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	hand_R->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHandN);

	head->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	head->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHeadN);

	leg_L->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	leg_L->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerLegN);

	leg_R->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	leg_R->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerLegN);

	for (auto* m : models)
	{
		auto* appe = m->GetAppearance(0);
		//使用するシェーダーの選択
		appe->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

		//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
		appe->SetUsingTextureFromContainer(1, 1, 0, 0);

	}

	Load();

}

void PlayerModel::Reset()
{}
