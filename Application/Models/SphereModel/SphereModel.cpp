#include "SphereModel.h"

void SphereModel::SetCurrentSize(float size)
{
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	float rate = size / defaultScale.x;

	appearance->trans.scale.x = rate;
	appearance->trans.scale.y = rate;
	appearance->trans.scale.z = rate;
}

SphereModel::SphereModel()
{
	//モデルの生成(必須)
	model = M::GetInstance()->CreateModel("./resource/application/Model/Effects/HalfSphere/HalfSphere.gltf");
	//model = M::GetInstance()->CreateModel("./resource/application/Model/Effects/Plane/Plane.obj");
	//model = M::GetInstance()->CreateModel("./resource/application/Model/Effects/Circle/Circle.obj");
}

void SphereModel::Update(int mode_, float count_)
{
	if (mode_ == 3)
	{

	}

}

void SphereModel::Draw(Matrix4 * vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
}

void SphereModel::Init(Transform * gameObjectTrans_)
{
	//↓↓↓↓↓必須↓↓↓↓↓

	//見た目のパラメーター
	//複数モデルを考慮しているためインデックスで指定する
	auto* appearance = model->GetAppearance(0);
	//使用するシェーダーの選択
	appearance->shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");

	appearance->trans.pos.y = 0.2f;

	appearance->use_texHandles[Appearance::kColormap] =
		M::GetInstance()->GetTexIndex(TextureTag::kGridN);
	//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
	appearance->SetUsingTextureFromContainer(1, 0, 0, 0);
	appearance->color = { 200,200,255,255 };

	//ゲームオブジェクトと全モデルのペアレント化
	MakeAllPartsBeChildren(gameObjectTrans_);

	//appearance->cullMode = CullMode::kCullModeNone;
	//appearance->blendMode = BlendMode::kBlendModeAdd;
}

void SphereModel::Reset()
{}
