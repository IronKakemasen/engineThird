#include "PlayerModel.h"

void PlayerModel::Save()
{
	std::string key = "/ID/";
	int i = 0;
	for (auto* m : models)
	{
		Json::SaveParam(path, key + "pos" + std::to_string(i),
			m->Getter_Appearance(0)->trans.pos);
		Json::SaveParam(path, key + "rotation" + std::to_string(i),
			m->Getter_Appearance(0)->trans.rotation);
		Json::SaveParam(path, key + "lookDir" + std::to_string(i),
			m->Getter_Appearance(0)->trans.lookDir);

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
			m->Getter_Appearance(0)->trans.pos);
		Json::LoadParam(path, key + "rotation" + std::to_string(i),
			m->Getter_Appearance(0)->trans.rotation);
		Json::LoadParam(path, key + "lookDir" + std::to_string(i),
			m->Getter_Appearance(0)->trans.lookDir);

		++i;
	}
}

PlayerModel::PlayerModel()
{
	//モデルの生成(必須)
	body = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Body/Player_Body.obj");
	hand_L = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Hand_L/Player_Hand_L.obj");
	hand_R = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Hand_R/Player_Hand_R.obj");
	head = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Head/Player_Head.obj");
	leg_L = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Leg_L/Player_Leg_L.obj");
	leg_R = M::GetInstance()->CreateModel("./resource/application/Model/PlayerModels/Player_Leg_R/Player_Leg_R.obj");

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

	//ゲームオブジェクトと全モデルのペアレント化
	body->Getter_Appearance(0)->trans.BeChildren(gameObjectTrans_);
	hand_L->Getter_Appearance(0)->trans.BeChildren(&body->Getter_Appearance(0)->trans);
	hand_R->Getter_Appearance(0)->trans.BeChildren(&body->Getter_Appearance(0)->trans);
	head->Getter_Appearance(0)->trans.BeChildren(&body->Getter_Appearance(0)->trans);
	leg_L->Getter_Appearance(0)->trans.BeChildren(&body->Getter_Appearance(0)->trans);
	leg_R->Getter_Appearance(0)->trans.BeChildren(&body->Getter_Appearance(0)->trans);

	//↑↑↑↑↑必須↑↑↑↑↑

	for (auto* m : models)
	{
		auto* appe = m->Getter_Appearance(0);
		appe->metalic = 0.0f;
		appe->roughness = 1.0f;
		//使用するシェーダーの選択
		appe->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");

		//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
		appe->SetUsingTextureFromContainer(1, 0, 0, 0);

	}

	Load();

	//appearance->metalic = 0.72f;
	//appearance->roughness = 0.4f;
	//appearance->color = { 0,255,0,255 };


}

void PlayerModel::Reset()
{}
