#include "EnemyFactory.h"
#include "../Json/Json.h"
#include "imgui.h"

EnemyFactory::EnemyFactory()
{
	//モデルのインスタンス化
	model.reset(new EnemyFactoryModel);
	//必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };
}

void EnemyFactory::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();
}

void EnemyFactory::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kEnemyFactory);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackToPlayerBulletの初期化
	collisionBackToPlayerBullet.Init(this);
}

void EnemyFactory::SetCollisionBackTable()
{
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
}

void EnemyFactory::LoadData()
{
	// Jsonからデータをロード
	Json::LoadParam("./resource/application/json/enemy/enemyFactory.json", "position", trans.pos);
}

void EnemyFactory::SaveData()
{
	Json::SaveParam("./resource/application/json/enemy/enemyFactory.json", "position", trans.pos);
	Json::Save("./resource/application/json/enemy/enemyFactory.json");
}

void EnemyFactory::Update()
{
	model->Update();
}

void EnemyFactory::Draw(Matrix4 * vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
}

void EnemyFactory::DebugDraw()
{
#ifdef USE_IMGUI
	
	ImGui::DragFloat3("EnemyFactoryPos", &trans.pos.x, 0.1f);
	if (ImGui::Button("Save"))
	{
		SaveData();
	}
	if (ImGui::Button("Load"))
	{
		LoadData();
	}

#endif // USE_IMGUI
}

// プレイヤー弾との衝突
void EnemyFactory::CollisionBackToPlayerBullet::operator()()
{
	me->SetStatus(Status::kInActive);
}


