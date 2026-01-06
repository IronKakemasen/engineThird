#include "PlayerModel.h"

void PlayerModel::Update()
{

}

void PlayerModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

PlayerModel::PlayerModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/Player/Player.obj");

	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");

	//使用するテクスチャの選択
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);

}

void PlayerModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.metalic = 0.1f;
	appearance0.roughness = 0.8f;
	appearance0.color = { 255,255,150,255 };

}

void PlayerModel::Reset()
{

}

