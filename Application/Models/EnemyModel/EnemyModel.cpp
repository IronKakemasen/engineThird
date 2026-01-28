#include "EnemyModel.h"

EnemyModel::EnemyModel()
{
	//モデルの生成(必須)
	body = M::GetInstance()->CreateModel("./resource/application/Model/Enemy04/Enemy/E_Body/E_Body.gltf");
	thorn = M::GetInstance()->CreateModel("./resource/application/Model/Enemy04/Enemy/E_Thorn/E_Thorn.gltf");

	models.emplace_back(body.get());
	models.emplace_back(thorn.get());

}

void EnemyModel::Update()
{
	for (auto* m : models)
	{
		auto* appe = m->Getter_Appearance(0);
		appe->trans.rotation.y += 3.0f;

	}
}

void EnemyModel::Draw(Matrix4* vpMat_)
{
	for (auto* m : models)
	{
		M::GetInstance()->DrawModel(m, vpMat_);
	}
}

void EnemyModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	models[0]->Getter_Appearance(0)->trans.BeChildren(gameObjectTrans_);
	models[0]->Getter_Appearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kEnemyBodyN);
	models[0]->Getter_Appearance(0)->trans.pos.y += 0.25f;
	models[1]->Getter_Appearance(0)->trans.BeChildren(&models[0]->Getter_Appearance(0)->trans);
	models[1]->Getter_Appearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kEnemyThornN);

	for (auto* m : models)
	{
		auto* appe = m->Getter_Appearance(0);
		//使用するシェーダーの選択
		appe->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

		//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
		appe->SetUsingTextureFromContainer(1, 1, 0, 0);

		//必須でない
		appe->metalic = 0.72f;
		appe->roughness = 0.4f;
		appe->color = { 200,50,50,255 };
	}


}

void EnemyModel::Reset()
{

}
