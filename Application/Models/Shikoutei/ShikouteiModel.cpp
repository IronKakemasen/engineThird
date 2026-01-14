#include "ShikouteiModel.h"

ShikouteiModel::ShikouteiModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/preset/model/Block/Block.obj");

}

void ShikouteiModel::Update()
{
	
}

void ShikouteiModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void ShikouteiModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓
	
	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->Getter_Appearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//↑↑↑↑↑必須↑↑↑↑↑

	//必須でない
	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };

}

void ShikouteiModel::Reset()
{
}
