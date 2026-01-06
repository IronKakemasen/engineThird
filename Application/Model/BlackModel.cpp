#include "BlackModel.h"

void BlackModel::Update()
{

}

void BlackModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

BlackModel::BlackModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/Block/Block.obj");

	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャの選択
	appearance0.texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kGridN);
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);
}

void BlackModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.metalic = 0.92f;
	appearance0.roughness = 0.1f;
	appearance0.color = { 32,32,32,255 };

}

void BlackModel::Reset()
{

}

