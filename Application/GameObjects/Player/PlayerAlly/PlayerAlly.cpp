#include "PlayerAlly.h"
#include "imgui.h"
#include "../../../GameObjects/Player/Player.h"
#include "../../../M/utilities/Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../../Config/InGameConfig.h"

PlayerAlly::PlayerAlly()
{
	// モデルのインスタンス化
	model.reset(new PlayerAllyModel);

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
	SetCircleCollision(inGameConfig->playerAllyCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);
	// プレイヤーポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
	collisionBackToPlayerBullet.Init(this);

	// 補完係数設定
	trans.interpolationCoe = 0.9f;
}

void PlayerAlly::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
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

	if (nextState != PlayerAlly::State::kNone)
	{
		currentState = nextState;

		switch (nextState)
		{
		case PlayerAlly::State::kUnformed:
			break;
		case PlayerAlly::State::kFormed:
			break;
		case PlayerAlly::State::kLocked:
			break;
		case PlayerAlly::State::kDead:
			break;
		case PlayerAlly::State::kNone:
			break;
		default:
			break;
		}
	}
	nextState = PlayerAlly::State::kNone;

	// 更新
	switch (currentState)
	{
	case PlayerAlly::State::kUnformed:
		MoveToPlayer();
		break;
	case PlayerAlly::State::kFormed:
		FollowPlayer();
		break;
	case PlayerAlly::State::kLocked:
		LockPosition();
		break;
	case PlayerAlly::State::kDead:
		Death();
		break;
	case PlayerAlly::State::kNone:
		break;
	default:
		break;
	}
}

void PlayerAlly::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void PlayerAlly::DebugDraw()
{}


void PlayerAlly::MoveToPlayer()
{
	/// 自身の目標インデックスに対応する目標座標を取得(列の最後尾)
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);

	/// 現在地から最後尾ベクトル
	Vector3 direction = targetPos - trans.pos;

	/// 移動ベクトルを取得
	Vector3 moveVector = direction.GetNormalized() * (inGameConfig->playerSpeed * inGameConfig->playerAllySpeed);

	// 移動量より目的地までの距離が短い場合目的地に直接移動
	if (moveVector.GetMagnitutde() > direction.GetMagnitutde())
	{
		trans.pos = targetPos;

		// 最後尾予約
		int32_t tryFormationIndex = targetPlayer->TryReserveFormationIndex();

		// 成功すれば列に加入
		if (tryFormationIndex != -1)
		{
			// 自身のインデックス更新
			formationCurrentIndex = tryFormationIndex;

			// 状態遷移
			nextState = State::kFormed;
		}
	}
	/// 通常の移動処理
	else
	{
		trans.pos = trans.pos + (direction.GetNormalized() * (inGameConfig->playerSpeed * inGameConfig->playerAllySpeed));
	}
}

void PlayerAlly::FollowPlayer()
{
	/// そのフレームのAlly分離数を取得
	int32_t allySeparationCount = targetPlayer->GetSeparateAllyCount();

	/// 分離がある かつ 自身のインデックスが分離数以内なら
	if (allySeparationCount != -1 && formationCurrentIndex < allySeparationCount)
	{
		// 列から分離
		formationCurrentIndex = -1;
		// 状態遷移
		nextState = State::kLocked;

		return;
	}

	// 自身の目標インデックスに対応する目標座標を取得
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);
	// 目的地に直接移動
	trans.pos = targetPos;
}

void PlayerAlly::LockPosition()
{

}

void PlayerAlly::Spawn(Vector3 pos)
{
	// 有効化
	SetStatus(Status::kActive);
	// ステータスを設定
	currentState = State::kUnformed;
	// 初期座標設定
	trans.pos = pos;
	// 自分は列の何番目か
	formationCurrentIndex = -1;
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerAllyCollisonSize);
}

void PlayerAlly::Death()
{
	SetStatus(Status::kInActive);
}



// エネミーとの衝突
void PlayerAlly::CollisionBackToEnemy::operator()()
{
	if (me->currentState == PlayerAlly::State::kFormed || me->currentState == PlayerAlly::State::kLocked)
	{
		me->nextState = PlayerAlly::State::kDead;
	}
}

// プレイヤー弾との衝突
void PlayerAlly::CollisionBackToPlayerBullet::operator()()
{
	if (me->currentState == PlayerAlly::State::kFormed || me->currentState == PlayerAlly::State::kLocked)
	{
		me->nextState = PlayerAlly::State::kDead;
	}
}

// プレイヤーとの衝突
void PlayerAlly::CollisionBackToPlayer::operator()()
{
	if (me->currentState == PlayerAlly::State::kLocked)
	{
		me->nextState = PlayerAlly::State::kUnformed;
	}
}