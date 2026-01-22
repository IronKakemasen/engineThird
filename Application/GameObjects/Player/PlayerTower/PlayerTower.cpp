#include "PlayerTower.h"
#include "../Json/Json.h"

PlayerTower::PlayerTower()
{
	// モデルのインスタンス化
	model.reset(new PlayerTowerModel);

	// 必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 0,0,255,255 };

	// Jsonパスの設定
	path = "./resource/application/json/player/playerTowerData.json";
}

void PlayerTower::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// 初期無効化
	status = Status::kInActive;
}

void PlayerTower::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerTower);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
}

void PlayerTower::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

// データ保存・読み込み
void PlayerTower::LoadData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
}
void PlayerTower::SaveData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

void PlayerTower::Update()
{
	//モデルの更新処理
	model->Update();
}

void PlayerTower::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void PlayerTower::DebugDraw()
{}

// Enemyとの衝突
void PlayerTower::CollisionBackToEnemy::operator()()
{
	// 自身の取得
	auto* PlayerTower = me;
	me->trans.rotation.y += 1.0f;
}