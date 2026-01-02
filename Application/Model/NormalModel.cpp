#include "NormalModel.h"

void NormalModel::Update()
{

}

void NormalModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

NormalModel::NormalModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/Block/Block.obj");

	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャの選択

	//appearance0.texHandlesContainer[Appearance::kNormalmap] =
	//	M::GetInstance()->GetTexIndex(TextureTag::kBlackNormal);
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);
}

void NormalModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.metalic = 0.72f;
	appearance0.roughness = 0.4f;
	appearance0.color = { 128,128,128,255 };

}

void NormalModel::Reset()
{

}

