#include "PlayerAllyModel.h"

PlayerAllyModel::PlayerAllyModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Ally02/Ally/Ally_Body.gltf");

}

void PlayerAllyModel::Update()
{

}

void PlayerAllyModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void PlayerAllyModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->Getter_Appearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

	appearance->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kAllyN);

	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 1, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//↑↑↑↑↑必須↑↑↑↑↑

	//必須でない
	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
}

void PlayerAllyModel::Reset()
{}
