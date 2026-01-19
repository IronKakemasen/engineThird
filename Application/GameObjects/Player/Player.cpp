#include "Player.h"
#include "imgui.h"
#include "../Json/Json.h"

void Player::SaveData()
{
	Json::AddParam("./resource/json/player/playerData.json", "position", trans.pos);
	Json::AddParam("./resource/json/player/playerData.json", "velocity", velocity);
	Json::Save("./resource/json/player/playerData.json");
}

void Player::CollisionBackToEnemy::operator()()
{
	// 自身の取得
	auto* player = me;
	me->trans.rotation.y += 1.0f;
}

void Player::Update()
{
	//モデルの更新処理
	model->Update();

	translate = trans.pos;
	velocity = velocity + acceleration;
	translate = translate + velocity;


	if (M::GetInstance()->IsKeyPressed(KeyType::J))
	{
		SaveData();
	}

	if (M::GetInstance()->getPadState.IsHeld(0, PAD_LEFT))
	{
		translate.x -= 0.1f;
	}
	if (M::GetInstance()->getPadState.IsHeld(0, PAD_RIGHT))
	{
		translate.x += 0.1f;
	}
	if (M::GetInstance()->getPadState.IsHeld(0, PAD_UP))
	{
		translate.y += 0.1f;
		M::GetInstance()->getPadState.SetVibration(0, 0.0f, 0.0f);
	}
	if (M::GetInstance()->getPadState.IsHeld(0, PAD_DOWN))
	{
		translate.y -= 0.1f;
		M::GetInstance()->getPadState.SetVibration(0, 1.0f, 1.5f);
	}


	trans.pos = translate;
}

void Player::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::Player);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// Jsonからデータをロード
	Json::Load("./resource/json/player/playerData.json");
	Json::Load("./resource/json/player/playerData.json", "position", trans.pos);
	Json::Load("./resource/json/player/playerData.json", "velocity", velocity);
}

void Player::Reset()
{
	// モデルのリセット
	model->Reset();
}

void Player::Draw(Matrix4 * vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void Player::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::Enemy, collisionBackToEnemy);
}

Player::Player()
{
	// モデルのインスタンス化
	model.reset(new PlayerModel);
}
