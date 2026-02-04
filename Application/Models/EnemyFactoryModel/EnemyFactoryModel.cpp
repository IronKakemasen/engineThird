#include "EnemyFactoryModel.h"

EnemyFactoryModel::EnemyFactoryModel()
{
	//モデルの生成(必須)
	body = M::GetInstance()->CreateModel("./resource/application/Model/Factory/Factory.gltf");
	zenmai = M::GetInstance()->CreateModel("./resource/application/Model/Screw/Screw.gltf");
	models.emplace_back(body.get());
	models.emplace_back(zenmai.get());
	zenmaiCnt.Initialize(0.25f);
	zenmaiRotateCnt.Initialize(0.75f);
}

void EnemyFactoryModel::Update(int mode_ , float count_ )
{
	//どんなときもぜんまいくるくる
	zenmaiCnt.Add();
	if (zenmaiCnt.count >=1.0f)
	{
		static float const addNum = 67.5f;
		zenmai->GetAppearance(0)->trans.rotation.y =
			Easing::EaseOutElastic(curRotateDegree, curRotateDegree + addNum, zenmaiRotateCnt.count);
		
		if (zenmaiRotateCnt.IsEnd())
		{
			curRotateDegree += addNum;
			zenmaiCnt.count = 0.0f;
		}

		zenmaiRotateCnt.Add();

	}

	//被ダメリアクションでないとき
	if ((mode_ != 1) && (mode_ != 3))
	{
		return;
		body->GetAppearance(0)->trans.pos.x = 0.0f;
		zenmai->GetAppearance(0)->trans.pos.x = 0.0f;

		shakeDeltaTheta = 0.0f;
	}

	if (mode_ != 3)
	{
		for (auto* m : models)
		{
			auto* a = m->GetAppearance(0);
			a->color.w = 255.0f;
		}
	}

	if (mode_ == 1)
	{
		for (auto* m : models)
		{
			auto* a = m->GetAppearance(0);

			float dstAmp = 0.0f;
			float exclusive = count_;

			if (exclusive != 0.0f)
			{
				dstAmp = kMaxAmplitude * 1.0f / exclusive;
			}

			shakeDeltaTheta += kShakeSpeed;

			float deltaX = sinf(shakeDeltaTheta) * dstAmp;

			a->trans.pos.x = deltaX;

		}
	}
	else if (mode_ == 3)
	{
		for (auto* m : models)
		{
			auto* a = m->GetAppearance(0);
			a->color.w *= 0.985f;

		}
	}

}

void EnemyFactoryModel::Draw(Matrix4* vpMat_)
{
	for (auto* m : models)
	{
		M::GetInstance()->DrawModel(m, vpMat_);
	}
}

void EnemyFactoryModel::Init(Transform* gameObjectTrans_)
{
	body->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kFactoryN);

	zenmai->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		M::GetInstance()->GetTexIndex(TextureTag::kScrewN);

	body->GetAppearance(0)->trans.BeChildren(gameObjectTrans_);
	zenmai->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	zenmai->GetAppearance(0)->trans.pos.y = 3.25f;
	zenmai->GetAppearance(0)->trans.pos.z = -1.0f;


	for (auto* m : models)
	{
		auto* appearance = m->GetAppearance(0);
		//使用するシェーダーの選択
		appearance->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");
		appearance->color = { 200,50,20,255 };
		appearance->trans.lookDir = { -1,0,0 };
		//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
		appearance->SetUsingTextureFromContainer(1, 1, 0, 0);
	}


}

void EnemyFactoryModel::Reset()
{}
