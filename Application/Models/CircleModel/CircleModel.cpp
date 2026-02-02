#include "CircleModel.h"

CircleModel::CircleModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Effects/Circle/Circle.obj");
}

void CircleModel::Update(int mode_, float count_)
{
	auto* appearance = model->GetAppearance(0);
	deltaTheta += 0.035f;
	float t = sinf(deltaTheta) * 0.35f;

	appearance->trans.scale.x = defaultScale.x + t;
	appearance->trans.scale.z = defaultScale.z + t;


}

void CircleModel::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void CircleModel::Init(Transform* gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");

	appearance->trans.pos.y = 0.2f;

	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//appearance->cullMode = CullMode::kCullModeNone;
	appearance->blendMode = BlendMode::kBlendModeAdd;
}

void CircleModel::Reset()
{

}
