#include "GroundPlane.h"

GroundPlane::GroundPlane()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Ground02/Ground/Ground.gltf");
}

void GroundPlane::Update()
{

}

void GroundPlane::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void GroundPlane::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

//見た目のパラメーター
//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");

	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//↑↑↑↑↑必須↑↑↑↑↑

	//必須でない
	appearance->metalic = 0.0f;
	appearance->roughness = 0.5f;
	appearance->trans.pos.y = -30;
}

void GroundPlane::Reset()
{

}
