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
	collisionBackToPlayerBullet.Init(this);

	// ポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);

	// 補完係数設定
	trans.interpolationCoe = 0.9f;
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

//void PlayerAlly::Move()
//{
//	uint32_t formationTargetIndex = targetPlayer->GetNextEmptyAllyIndex(formationCurrentIndex);
//	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationTargetIndex);
//	Vector3 direction = targetPos - trans.pos;
//	direction = direction.GetNormalized();
//
//	// -1(列に加わっていない野良)なら最後尾に向かう
//	if (formationCurrentIndex == -1)
//	{
//		// 補完
//		trans.lookDir = Easing::SLerp(trans.lookDir, direction, trans.interpolationCoe);
//
//		trans.pos = trans.pos + (trans.lookDir * (targetPlayer->GetSpeed() / 3.0f));
//
//		// 目的地に到達したら位置を合わせる
//		if (Vector3(targetPos - trans.pos).GetMagnitutde() < 0.5f)
//		{
//			// たどり着いたインデックスにまだ味方がいなければ列に登録
//			if (targetPlayer->allyExistenceFlags[formationTargetIndex] == false)
//			{
//				// 自身のインデックス更新
//				formationCurrentIndex = formationTargetIndex;
//
//				// 味方存在フラグ更新
//				targetPlayer->allyExistenceFlags[formationTargetIndex] = true;
//			}
//		}
//	}
//	else
//	{
//		trans.pos = targetPos;
//	}
//}

//void PlayerAlly::Move()
//{
//	uint32_t formationTargetIndex = targetPlayer->GetNextEmptyAllyIndex(formationCurrentIndex);
//	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationTargetIndex);
//	Vector3 direction = targetPos - trans.pos;
//	float distance = direction.GetMagnitutde();
//
//
//	// 目的地まで距離があるなら移動
//	if (distance > 0.2f)
//	{
//		// 補完
//		trans.lookDir = Easing::SLerp(trans.lookDir, direction.GetNormalized(), trans.interpolationCoe);
//
//		trans.pos = trans.pos + (trans.lookDir * (targetPlayer->GetSpeed()));
//
//		distance = Vector3(targetPos - trans.pos).GetMagnitutde();
//
//		// 移動した結果目的地に到達したなら かつ
//		if (distance < 0.2f)
//		{
//			// たどり着いたインデックスにまだ味方がいなければ 列に登録
//			if (targetPlayer->allyExistenceFlags[formationTargetIndex] == false)
//			{
//				// 自身のインデックス更新
//				formationCurrentIndex = formationTargetIndex;
//
//				// 味方存在フラグ更新
//				targetPlayer->allyExistenceFlags[formationTargetIndex] = true;
//			}
//		}
//	}
//	// 目的地に近ければ理想の位置に移動
//	else
//	{
//		trans.pos = targetPos;
//	}
//}

void PlayerAlly::Move()
{
	formationTargetIndex = targetPlayer->GetNextEmptyAllyIndex(formationCurrentIndex);
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);
	Vector3 direction = targetPos - trans.pos;
	float distance = direction.GetMagnitutde();


	// 目的地まで距離があるなら移動
	if (distance > 0.2f)
	{
		trans.pos = trans.pos + (direction.GetNormalized() * targetPlayer->GetSpeed());

		distance = Vector3(targetPos - trans.pos).GetMagnitutde();

		// 移動した結果目的地に到達したなら かつ
		if (distance < 0.2f)
		{
			// たどり着いたインデックスにまだ味方がいなければ 列に登録
			if (targetPlayer->allyExistenceFlags[formationTargetIndex] == false)
			{
				// 自身のインデックス更新
				formationCurrentIndex = formationTargetIndex;

				// 味方存在フラグ更新
				targetPlayer->allyExistenceFlags[formationTargetIndex] = true;
			}
		}
	}
	// 目的地に近ければ理想の位置に移動
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
	me->SetStatus(Status::kInActive);
}