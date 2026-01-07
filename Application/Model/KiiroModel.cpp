#include "KiiroModel.h"

void KiiroModel::Update()
{

}

void KiiroModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

KiiroModel::KiiroModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/Kiiro/Kiiro.obj");

	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelNoLight.VS", "ModelNoLight.PS");

	//使用するテクスチャの選択
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);
	appearance0.blendMode = BlendMode::kBlendModeAdd;
}

void KiiroModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.color = { 255,255,150,255 };

}

void KiiroModel::Reset()
{

}

