#include "SampleModel2.h"
#include "../../../../../external/imgui/imgui.h"
void SampleModel2::Update()
{

}

void SampleModel2::Draw(Matrix4* vpMat_)
{
	M::GetInstance()->DrawModel(model.get(), vpMat_);
	ImGui::Begin("ioehc");
	ImGui::DragFloat("metalic", &(*model->Getter_Appearance())[0].metalic, 0.01f);
	ImGui::DragFloat("roughness", &(*model->Getter_Appearance())[0].roughness, 0.01f);

	ImGui::End();
}

SampleModel2::SampleModel2()
{
	//model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/nomalMappedTeapot/teapot.obj");
	//model->Getter_ModelData().appearance[0].shaderSetIndex =
	//M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");
	//model->Getter_ModelData().appearance[0].SetUsingTextureFromContainer(1, 1, 0, 0);

	////モデルの生成
	//model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/teapot/teapot.obj");
	////使用するシェーダーの選択
	//model->Getter_ModelData().appearance[0].shaderSetIndex =
	//M::GetInstance()->GetShaderSetIndexFromFileName("ModelSimple.VS", "ModelSimple.PS");
	////使用するテクスチャの選択
	//model->Getter_ModelData().appearance[0].SetUsingTextureFromContainer(1, 0, 0, 0);

	////モデルの生成
	//model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/teapot/teapot.obj");
	////使用するシェーダーの選択
	//(*model->Getter_Appearance())[0].shaderSetIndex =
	//	M::GetInstance()->GetShaderSetIndexFromFileName("ModelPhong.VS", "ModelPhong.PS");
	////使用するテクスチャの選択
	//(*model->Getter_Appearance())[0].SetUsingTextureFromContainer(1, 0, 0, 0);

	////モデルの生成
	//model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/teapot/teapot.obj");
	////使用するシェーダーの選択
	//(*model->Getter_Appearance())[0].shaderSetIndex =
	//	M::GetInstance()->GetShaderSetIndexFromFileName("ModelCookTorrance.VS", "ModelCookTorrance.PS");
	////使用するテクスチャの選択
	//(*model->Getter_Appearance())[0].SetUsingTextureFromContainer(1, 0, 0, 0);

	//モデルの生成
	model = M::GetInstance()->CreateModel("./M/resource/preset/model/test/teapot/teapot.obj");
	//使用するシェーダーの選択
	(*model->Getter_Appearance())[0].shaderSetIndex =
		M::GetInstance()->GetShaderSetIndexFromFileName("ModelGGX.VS", "ModelGGX.PS");
	//使用するテクスチャの選択
	(*model->Getter_Appearance())[0].SetUsingTextureFromContainer(1, 0, 0, 0);

}

void SampleModel2::Init()
{
	(*model->Getter_Appearance())[0].trans.pos.x = 0.5f;
	(*model->Getter_Appearance())[0].metalic = 0.72f;
	(*model->Getter_Appearance())[0].roughness = 0.4f;
}

void SampleModel2::Reset()
{

}
