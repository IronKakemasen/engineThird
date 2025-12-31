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
	model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/axis.obj");
	auto& appearance0 = (*model->Getter_Appearance())[0];

	//使用するシェーダーの選択
	appearance0.shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャの選択
	appearance0.SetUsingTextureFromContainer(1, 0, 0, 0);


}

void BlackModel::Init()
{
	auto& appearance0 = (*model->Getter_Appearance())[0];
	appearance0.trans.pos.x = -0.5f;
	appearance0.metalic = 0.72f;
	appearance0.roughness = 0.4f;
}

void BlackModel::Reset()
{

}

