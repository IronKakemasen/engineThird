#include "PlaneModel.h"

void PlaneModel::Update()
{

}

void PlaneModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

PlaneModel::PlaneModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/Mark/Mark.obj");

	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelNoLight.VS", "ModelNoLight.PS");

	//使用するテクスチャの選択
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);
	appearance0.blendMode = BlendMode::kBlendModeAdd;
}

void PlaneModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.color = { 255,255,150,255 };

}

void PlaneModel::Reset()
{

}

