#include "PlayerBulletModel.h"

PlayerBulletModel::PlayerBulletModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/PlayerBullet/PlayerBullet.gltf");

}

void PlayerBulletModel::Update(int mode_, float count_)
{
	auto* appearance = model->GetAppearance(0);

	appearance->trans.rotation.z += rotateSpeed;
}

void PlayerBulletModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void PlayerBulletModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

	appearance->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kBulletN);

	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 1, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//↑↑↑↑↑必須↑↑↑↑↑

	//必須でない
	appearance->metalic = 0.0f;
	appearance->roughness = 0.0f;
	appearance->trans.pos.y = 3.0f;
	appearance->color = { 200,200,0,255 };
}

void PlayerBulletModel::Reset()
{}
