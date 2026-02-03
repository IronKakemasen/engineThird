#include "PlayerModel.h"


void PlayerModel::Update(int mode_, float count_)
{
	//mode_ = 1;
	if (mode_ == 0)
	{
		IdleInGame();
	}
	else if (mode_ == 1)
	{
		Run();
	}
	else
	{
		Idle();
	}
}

void PlayerModel::Idle()
{
	float const loopSpeed = 0.15f;
	idleDelta += loopSpeed;

	auto* h = head->GetAppearance(0);
	auto* b = body->GetAppearance(0);
	auto* legr = leg_R->GetAppearance(0);
	auto* legl = leg_L->GetAppearance(0);
	auto* arml = hand_L->GetAppearance(0);
	auto* armr = hand_R->GetAppearance(0);

	if (headRotateCnt.count >= 0.0f && headRotateCnt.count < 0.2f)
	{
		float const bodyDefaultY = 0.5f;
		float const legDefaultY = -0.4f;

		float numTizimi = 0.2f;

		//縮んで
		if (headRotateCnt.count < 0.1f)
		{
			float t = Counter::GetNormalizedCount(0.0f, 0.1f, headRotateCnt.count);

			b->trans.pos.y = Easing::EaseOutSine(bodyDefaultY, bodyDefaultY - numTizimi, t);
			legr->trans.pos.y = Easing::EaseOutSine(legDefaultY, legDefaultY + numTizimi, t);
			legl->trans.pos.y = Easing::EaseOutSine(legDefaultY, legDefaultY + numTizimi, t);
		}
		//伸びる
		else
		{
			float t = Counter::GetNormalizedCount(0.1f, 0.2f, headRotateCnt.count);

			b->trans.pos.y = Easing::EaseOutElastic(bodyDefaultY - numTizimi, bodyDefaultY , t);
			legr->trans.pos.y = Easing::EaseOutElastic(legDefaultY + numTizimi, legDefaultY, t);
			legl->trans.pos.y = Easing::EaseOutElastic(legDefaultY + numTizimi, legDefaultY, t);
		}
		
	}

	//頭回転
	if (headRotateCnt.count >= 0.1f && headRotateCnt.count < 0.5f)
	{
		float t = Counter::GetNormalizedCount(0.1f, 0.5f, headRotateCnt.count);
		h->trans.rotation.x = Easing::EaseOutExpo(0.0f, -720.0f, t);

		float const maxHeight = 3.0f;
		float headDefaultY = 0.5199999809265137;
		if (headRotateCnt.count >= 0.1f && headRotateCnt.count < 0.4f)
		{
			float tt = Counter::GetNormalizedCount(0.1f, 0.4f, headRotateCnt.count);
			h->trans.pos.y = Easing::EaseOutCubic(headDefaultY, headDefaultY + maxHeight, tt);

		}
		else if (headRotateCnt.count >= 0.4f && headRotateCnt.count < 0.45f)
		{
			float tt = Counter::GetNormalizedCount(0.4f, 0.45f, headRotateCnt.count);
			h->trans.pos.y = Easing::EaseOutExpo(headDefaultY + maxHeight, headDefaultY , tt);

		}
	}

	if (headRotateCnt.count >= 0.4f && headRotateCnt.count < 0.5f)
	{
		float const bodyDefaultY = 0.5f;
		float const legDefaultY = -0.4f;

		float numTizimi = 0.2f;

		float t = Counter::GetNormalizedCount(0.4f, 0.5f, headRotateCnt.count);

		//縮んで
		if (t < 0.5f)
		{
			float tt = Counter::GetNormalizedCount(0.0f, 0.5f, t);

			b->trans.pos.y = Easing::EaseOutCubic(bodyDefaultY, bodyDefaultY - numTizimi, t);
			legr->trans.pos.y = Easing::EaseOutCubic(legDefaultY, legDefaultY + numTizimi, t);
			legl->trans.pos.y = Easing::EaseOutCubic(legDefaultY, legDefaultY + numTizimi, t);
		}
		//伸びる
		else
		{
			float tt = Counter::GetNormalizedCount(0.5f, 1.0f, t);

			b->trans.pos.y = Easing::EaseInExpo(bodyDefaultY - numTizimi, bodyDefaultY, t);
			legr->trans.pos.y = Easing::EaseInExpo(legDefaultY + numTizimi, legDefaultY, t);
			legl->trans.pos.y = Easing::EaseInExpo(legDefaultY + numTizimi, legDefaultY, t);
		}

	}

	if (headRotateCnt.count >= 0.6f && headRotateCnt.count < 0.9f)
	{
		float t = Counter::GetNormalizedCount(0.6f, 0.9f, headRotateCnt.count);

		float c = sinf(6.28f * t) * 45.0f;
		float cc = sinf(3.14f * t) * -22.5f;
		h->trans.rotation.y = c;
		h->trans.rotation.x = cc;

	}


	headRotateCnt.Add();
	headRotateCnt.IsEnd();
}

void PlayerModel::IdleInGame()
{
	auto* h = head->GetAppearance(0);
	auto* b = body->GetAppearance(0);
	auto* legr = leg_R->GetAppearance(0);
	auto* legl = leg_L->GetAppearance(0);
	auto* arml = hand_L->GetAppearance(0);
	auto* armr = hand_R->GetAppearance(0);

	float const bodyDefaultY = 0.5f;
	float const legDefaultY = -0.4f;

	h->trans.rotation.x = 0;

	b->trans.pos.y = bodyDefaultY;
	b->trans.rotation.x = 0;

	legr->trans.rotation.x = 0;
	legl->trans.rotation.x = 0;

	arml->trans.rotation.x = 0;
	armr->trans.rotation.x = 0;

	legr->trans.pos.y = legDefaultY;
	legl->trans.pos.y = legDefaultY;

	h->trans.rotation.y = 0.0f;
	h->trans.rotation.x = 0.0f;


}

void PlayerModel::Run()
{
	idleDelta = 0.0f;
	headRotateCnt.count = 0.0f;
	float const amp = 0.3f;
	float const loopSpeed = 0.225f;

	runDelta += loopSpeed;
	float deltaBodyY = sinf(runDelta) * amp;
	float deltaHuri = sinf(runDelta * 0.5f) * 45.0f;

	auto* h = head->GetAppearance(0);
	auto* b = body->GetAppearance(0);
	auto* legr = leg_R->GetAppearance(0);
	auto* legl = leg_L->GetAppearance(0);
	auto* arml = hand_L->GetAppearance(0);
	auto* armr = hand_R->GetAppearance(0);

	h->trans.rotation.x = 7.5f;

	b->trans.pos.y = 0.65f + deltaBodyY;
	b->trans.rotation.x = -12.5f;

	legr->trans.rotation.x = deltaHuri;
	legl->trans.rotation.x = -deltaHuri;

	arml->trans.rotation.x = deltaHuri;
	armr->trans.rotation.x = -12.5f;

}

void PlayerModel::Save()
{
	std::string key = "/ID/";
	int i = 0;
	for (auto* m : models)
	{
		Json::SaveParam(path, key + "pos" + std::to_string(i),
			m->GetAppearance(0)->trans.pos);
		Json::SaveParam(path, key + "rotation" + std::to_string(i),
			m->GetAppearance(0)->trans.rotation);
		Json::SaveParam(path, key + "lookDir" + std::to_string(i),
			m->GetAppearance(0)->trans.lookDir);
		Json::SaveParam(path, key + "color" + std::to_string(i),
			m->GetAppearance(0)->color);

		++i;
	}

	Json::Save(path);
}

void PlayerModel::Load()
{
	std::string key = "/ID/";
	int i = 0;
	for (auto* m : models)
	{
		Json::LoadParam(path, key + "pos" + std::to_string(i),
			m->GetAppearance(0)->trans.pos);
		Json::LoadParam(path, key + "rotation" + std::to_string(i),
			m->GetAppearance(0)->trans.rotation);
		Json::LoadParam(path, key + "lookDir" + std::to_string(i),
			m->GetAppearance(0)->trans.lookDir);
		Json::LoadParam(path, key + "color" + std::to_string(i),
			m->GetAppearance(0)->color);

		++i;
	}
}

PlayerModel::PlayerModel()
{
	//モデルの生成(必須)
	body = M::GetInstance()->CreateModel(  "./resource/application/Model/Player/P_Body/P_Body.gltf");
	hand_L = M::GetInstance()->CreateModel("./resource/application/Model/Player/P_Hand_L/P_Hand_L.gltf");
	hand_R = M::GetInstance()->CreateModel("./resource/application/Model/Player/P_Hand_R/P_Hand_R.gltf");
	head = M::GetInstance()->CreateModel(  "./resource/application/Model/Player/P_Head/P_Head.gltf");
	leg_L = M::GetInstance()->CreateModel( "./resource/application/Model/Player/P_Leg_L/P_Leg_L.gltf");
	leg_R = M::GetInstance()->CreateModel( "./resource/application/Model/Player/P_Leg_R/P_Leg_R.gltf"); 
	cannon = M::GetInstance()->CreateModel("./resource/application/Model/Cannon/Common.gltf");

	models.emplace_back(body.get());
	models.emplace_back(hand_L.get());
	models.emplace_back(hand_R.get());
	models.emplace_back(head.get());
	models.emplace_back(leg_L.get());
	models.emplace_back(leg_R.get());
	models.emplace_back(cannon.get());	
	headRotateCnt.Initialize(8.0f);
}


void PlayerModel::Draw(Matrix4* vpMat_)
{
	for (auto* m : models)
	{
		M::GetInstance()->DrawModel(m, vpMat_);

	}
}

void PlayerModel::Init(Transform* gameObjectTrans_)
{
	auto* m = M::GetInstance();

	//ゲームオブジェクトと全モデルのペアレント化
	body->GetAppearance(0)->trans.BeChildren(gameObjectTrans_);
	body->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap]=
		m->GetTexIndex(TextureTag::kPlayerBodyN);

	hand_L->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	hand_L->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHandN);

	hand_R->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	hand_R->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHandN);

	head->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	head->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerHeadN);

	leg_L->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	leg_L->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerLegN);

	leg_R->GetAppearance(0)->trans.BeChildren(&body->GetAppearance(0)->trans);
	leg_R->GetAppearance(0)->texHandlesContainer[Appearance::kNormalmap] =
		m->GetTexIndex(TextureTag::kPlayerLegN);

	auto* cannonAppe = cannon->GetAppearance(0);
	cannonAppe->trans.BeChildren(&hand_R->GetAppearance(0)->trans);
	cannonAppe->texHandlesContainer[Appearance::kNormalmap] = m->GetTexIndex(TextureTag::kCannonN);
	cannonAppe->trans.pos.z = 1.0f;
	cannonAppe->color = { 255,45,0,255 };
	cannonAppe->metalic = 0.52f;
	cannonAppe->roughness = 0.59f;
	for (auto* m : models)
	{
		auto* appe = m->GetAppearance(0);
		//使用するシェーダーの選択
		appe->shaderSetIndex =
			M::GetInstance()->GetShaderSetIndexFromFileName("ModelBump.VS", "ModelBump.PS");

		//使用するテクスチャ種類の選択(カラーマップ、ノーマルマップ、...)
		appe->SetUsingTextureFromContainer(1, 1, 0, 0);

	}

	Load();

}

void PlayerModel::Reset()
{}
