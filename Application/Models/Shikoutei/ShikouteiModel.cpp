#include "ShikouteiModel.h"

ShikouteiModel::ShikouteiModel()
{
	//モデルの生成
	model = M::GetInstance()->CreateModel("./resource/preset/model/test/axis.obj");

}

void ShikouteiModel::Update()
{

}

void ShikouteiModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void ShikouteiModel::Init()
{
	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->Getter_Appearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);

}
void ShikouteiModel::Reset()
{

}
