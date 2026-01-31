#include "PlayerAllyModel.h"

PlayerAllyModel::PlayerAllyModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Ally02/Ally/Ally_Body.gltf");

}

void PlayerAllyModel::Update(int mode_, float count_)
{
	auto* appearance = model->GetAppearance(0);
	MoveAnim(0);
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
	auto* appearance = model->GetAppearance(0);
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

	moveAnimCnt.Initialize(1.0f);
	idleCnt.Initialize(5.0f);
	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->trans.pos.y = 0.125f;
	appearance->color = { 50.0f,100.0f,255.0f,255.0f };
	appearance->trans.rotation.y = 180.0f;

}

void PlayerAllyModel::Reset()
{
	moveAnimCnt.Initialize(1.0f);
	pyonNum = 0;
	idleCnt.count = 0.95f;

}

void PlayerAllyModel::MoveAnim(int animPattern_)
{
	auto* appearance = model->GetAppearance(0);
	static float const kizyunY = 0.125f;
	static float const maxY = 3.0f;

	//待機中であれば色を変えてアニメーションはしない
	if (animPattern_ == 1 && moveAnimCnt.count >= 1.0f)
	{
		appearance->color = { 200,255,50,255 };
		return;
	}

	appearance->color = { 60,60,255.0f,255.0f };

	idleCnt.Add();
	if (idleCnt.count<1.0f) return;


	if (moveAnimCnt.IsEnd())
	{
		pyonNum++;
		pyonPattern = pyonNum % 4;
		idleCnt.count = 0.0f;
	}

	if (moveAnimCnt.count >= 0.0f && moveAnimCnt.count < 0.5f)
	{
		float t = Counter::GetNormalizedCount(0.0f, 0.5f, moveAnimCnt.count);
		appearance->trans.pos.y =
			Easing::EaseOutCubic(kizyunY, maxY,t);

	}
	else
	{
		float t = Counter::GetNormalizedCount(0.5f, 1.0f, moveAnimCnt.count);
		appearance->trans.pos.y =
			Easing::EaseInExpo(maxY,kizyunY, t);
	}

	if (pyonPattern == 0)
	{
		appearance->trans.rotation.x =
			Easing::EaseOutCubic(0.0f, 360.0f, moveAnimCnt.count);
	}
	else if (pyonPattern == 1)
	{
		appearance->trans.rotation.x =
			Easing::EaseOutCubic(0.0f, -360.0f, moveAnimCnt.count);
	}

	else if (pyonPattern == 2)
	{
		appearance->trans.rotation.z =
			Easing::EaseOutCubic(0.0f, 360.0f, moveAnimCnt.count);
	}

	else if (pyonPattern == 3)
	{
		appearance->trans.rotation.z =
			Easing::EaseOutCubic(0.0f, -360.0f, moveAnimCnt.count);
	}

	moveAnimCnt.Add();

}
