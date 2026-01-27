#include "Tenkyu.h"

Tenkyu::Tenkyu()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Tenkyu/Tenkyu.obj");
}

void Tenkyu::Update()
{

}

void Tenkyu::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawShaderToy(model.get(), vpMat_);
}

void Tenkyu::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

//見た目のパラメーター
//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->Getter_Appearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("tft3RH.VS", "tft3RH.PS");


	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

}

void Tenkyu::Reset()
{

}
