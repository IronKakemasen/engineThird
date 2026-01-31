#include "PlayerTowerModel.h"

PlayerTowerModel::PlayerTowerModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/PlayerTower/PlayerTower.gltf");

}

void PlayerTowerModel::Update(int mode_, float count_)
{
	auto* a = model->GetAppearance(0);

	//被ダメリアクションでないとき
	if (mode_ != 1)
	{
		return;
		a->trans.pos.x = 0.0f;
		shakeDeltaTheta = 0.0f;
	}

	float dstAmp = 0.0f;
	float exclusive = 1.0f - count_;

	if (exclusive != 0.0f)
	{
		dstAmp = kMaxAmplitude * 1.0f / exclusive;
	}

	shakeDeltaTheta += kShakeSpeed;

	float deltaX = sinf(shakeDeltaTheta) * dstAmp;

	a->trans.pos.x = deltaX;

}

void PlayerTowerModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void PlayerTowerModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

	appearance->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kTowerN);
	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 1, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//↑↑↑↑↑必須↑↑↑↑↑

	//必須でない
	appearance->trans.pos.y = 1.5f;
	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 20,50,200,255 };
}

void PlayerTowerModel::Reset()
{}
