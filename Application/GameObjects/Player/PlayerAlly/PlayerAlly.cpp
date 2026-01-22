#include "PlayerAlly.h"
#include "imgui.h"
#include "../../../GameObjects/Player/Player.h"
#include "../../../M/utilities/Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"

PlayerAlly::PlayerAlly()
{
	// モデルのインスタンス化
	model.reset(new PlayerAllyModel);

	// 必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 0,0,255,255 };

	// Jsonパスの設定
	path = "./resource/application/json/player/playerAllyData.json";
}

void PlayerAlly::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// 初期無効化
	status = Status::kInActive;

	// データ読み込み
	LoadData();
}

void PlayerAlly::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerAlly);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);

	// ポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);


	// 初期化
	Reset();
}

void PlayerAlly::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

// データ保存・読み込み
void PlayerAlly::LoadData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
}
void PlayerAlly::SaveData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}


void PlayerAlly::Update()
{
	//モデルの更新処理
	model->Update();

	// 移動処理
	Move();
}

void PlayerAlly::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void PlayerAlly::DebugDraw()
{}

void PlayerAlly::Move()
{
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(targetPlayer->GetNextEmptyAllyIndex());

	trans.pos = targetPos;
}



// エネミーとの衝突
void PlayerAlly::CollisionBackToEnemy::operator()()
{}