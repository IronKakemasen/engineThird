#include "LightModel.h"

LightModel::LightModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Diamond/Diamond.obj");
}

void LightModel::Update(int mode_, float count_)
{

}

void LightModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawShaderToy(model.get(), vpMat_);
}

void LightModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

//見た目のパラメーター
//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("Mt2SzR.VS", "Mt2SzR.PS");


	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

}

void LightModel::Reset()
{

}
