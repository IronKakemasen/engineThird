#include "TitleLogo.h"
#include "imgui.h"

TitleLogo::TitleLogo()
{
	//モデルの生成(必須)
	L2.emplace_back(M::GetInstance()->CreateModel("./resource/application/Model/TitleLogo/TitleLogo_L.obj"));
	L2.emplace_back(M::GetInstance()->CreateModel("./resource/application/Model/TitleLogo/TitleLogo_L.obj"));
	O2.emplace_back(M::GetInstance()->CreateModel("./resource/application/Model/TitleLogo/TitleLogo_O.obj"));
	O2.emplace_back(M::GetInstance()->CreateModel("./resource/application/Model/TitleLogo/TitleLogo_O.obj"));

	auto* l0 = models.emplace_back(L2[0].get());
	l0->GetAppearance(0)->trans.pos = { -225,75,0 };
	auto* l1 = models.emplace_back(L2[1].get());
	l1->GetAppearance(0)->trans.pos = { 235,75,0 };

	auto* o0 = models.emplace_back(O2[0].get());
	o0->GetAppearance(0)->trans.pos = { -130,0,0 };
		
	auto* o1 = models.emplace_back(O2[1].get());
	o1->GetAppearance(0)->trans.pos = { 135.0f,0,0 };

}

void TitleLogo::Update(int mode_, float count_)
{

}

void TitleLogo::Draw(Matrix4* vpMat_)
{
	for (auto* m : models)
	{
		M::GetInstance()->DrawShaderToy(m, vpMat_);		
	}

}

void TitleLogo::Init(Transform* gameObjectTrans_)
{
	for (auto* m : models)
	{
		auto* appearance = m->GetAppearance(0);
		//使用するシェーダーの選択
		appearance->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("tft3RH.VS", "tft3RH.PS");
	}

}

void TitleLogo::Reset()
{

}
