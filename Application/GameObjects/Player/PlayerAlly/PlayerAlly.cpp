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

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);
	// プレイヤーポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerAlly);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
	collisionBackToPlayerBullet.Init(this);

	// 補完係数設定
	trans.interpolationCoe = 0.9f;

	// 初期無効化
	status = Status::kInActive;
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
	// ※１
	// もし formationCurrentIndexが-1(列に加わっていない)なら最後尾に向かう
	// ↳補完なし最短経路　プレイヤーと同じ速度

	// ※２
	// もし formationCurrentIndexが!-1(列に加わっている)なら理想の位置に移動
	// ↳プレイヤーの移動履歴を完璧に追従

	// ※３
	// もし 列に加わってる かつ 自分の前に味方がいないなら 詰める
	// ↳プレイヤーの移動履歴を完璧に追従 つまりプレイヤーが止まらなければ隙間が埋まることはない

	// 自身の目標インデックスに対応する目標座標を取得
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);

	// 列に加わっていない場合 ※１
	if (formationCurrentIndex == -1)
	{
		// 原罪地から最後尾
		Vector3 direction = targetPos - trans.pos;

		if (direction.GetMagnitutde() > 0.0001f)
		{
			trans.lookDir = Easing::SLerp(trans.lookDir, direction, trans.interpolationCoe);
			trans.pos = trans.pos + (trans.lookDir.GetNormalized() * targetPlayer->GetSpeed());
		}

		// 目的地に到達した かつ
		if (Vector3(targetPos - trans.pos).GetMagnitutde() < 0.05f)
		{
			int32_t tryFormationIndex = targetPlayer->TryReserveFormationIndex();
			if (tryFormationIndex != -1)
			{
				// 自身のインデックス更新
				formationCurrentIndex = tryFormationIndex;
			}
		}

		return;
	}
	// 列に加わっている場合 ※２ ※３
	else
	{
		trans.pos = targetPos;
	}
}

void PlayerAlly::Spawn(Vector3 pos)
{
	// 有効化
	SetStatus(Status::kActive);
	// 初期座標設定
	trans.pos = pos;
	// 自分は列の何番目か
	formationCurrentIndex = -1;
}

void PlayerAlly::Death()
{
	SetStatus(Status::kInActive);

	// プレイヤーに報告
	targetPlayer->NotifyAllyDeath(formationCurrentIndex);
}



// エネミーとの衝突
void PlayerAlly::CollisionBackToEnemy::operator()()
{
	// 本来はここで自身の死亡判定を行うべきだが、
	// statusが非アクティブになるとコリジョンが無効化されてしまい、
	// エネミー側で衝突判定が行えなくなるため、エネミー側で処理を行う(1024敗)
}

// プレイヤー弾との衝突
void PlayerAlly::CollisionBackToPlayerBullet::operator()()
{
	if (me->formationCurrentIndex != -1)
	{
		me->Death();
	}
}