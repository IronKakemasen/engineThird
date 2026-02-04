#include "UIPlane.h"

UIPlane::UIPlane()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/UIPlane/UIPlane.obj");

}

void UIPlane::Update(int mode_, float count_)
{

}

void UIPlane::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void UIPlane::Init(Transform* gameObjectTrans_)
{


//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelNoLight.VS", "ModelNoLight.PS");
	appearance->trans.rotation.x = 47.5f;


	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);

	appearance->cullMode = CullMode::kCullModeNone;

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

}

void UIPlane::Reset()
{

}
