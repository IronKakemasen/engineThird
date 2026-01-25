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

	// デバッグ用色更新
	UpdateDebugColor();

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

//void PlayerAlly::Move()
//{
//	formationTargetIndex = targetPlayer->GetAllyTargetIndex(formationCurrentIndex);
//	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);
//	Vector3 direction = targetPos - trans.pos;
//	float distance = direction.GetMagnitutde();
//
//
//	// 目的地まで距離があるなら移動
//	if (distance > 0.2f)
//	{
//		trans.pos = targetPos;
//
//		distance = Vector3(targetPos - trans.pos).GetMagnitutde();
//
//		// 移動した結果目的地に到達した かつ
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

//void PlayerAlly::Move()
//{
//	// ※１
//	// もし formationCurrentIndexが-1(列に加わっていない)なら最後尾に向かう
//	// ↳補完なし最短経路　プレイヤーと同じ速度
//
//	// ※２
//	// もし formationCurrentIndexが!-1(列に加わっている)なら理想の位置に移動
//	// ↳プレイヤーの移動履歴を完璧に追従
//
//	// ※３
//	// もし 列に加わってる かつ 自分の前に味方がいないなら 詰める
//	// ↳プレイヤーの移動履歴を完璧に追従 つまりプレイヤーが止まらなければ隙間が埋まることはない
//
//	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationCurrentIndex);
//	formationTargetIndex = targetPlayer->GetAllyTargetIndex(formationCurrentIndex);
//
//	// 列に加わっていない場合 ※１
//	if (formationCurrentIndex == -1)
//	{
//		// 列の最後尾に向かう
//		Vector3 direction = targetPos - trans.pos;
//
//		trans.lookDir = Easing::SLerp(trans.lookDir, direction, trans.interpolationCoe);
//		trans.pos = trans.pos + (trans.lookDir.GetNormalized() * targetPlayer->GetSpeed());
//
//		// 目的地に到達したら位置を合わせる
//		if (Vector3(targetPos - trans.pos).GetMagnitutde() < 0.02f)
//		{
//			// たどり着いたインデックスにまだ味方がいなければ列に登録
//			if (targetPlayer->allyExistenceFlags[formationTargetIndex] == false)
//			{
//				// 自身のインデックス更新
//				formationCurrentIndex = formationTargetIndex;
//				// 味方存在フラグ更新
//				targetPlayer->allyExistenceFlags[formationTargetIndex] = true;
//			}
//		}
//	}
//	// 列に加わっている場合 ※２ ※３
//	else
//	{
//		trans.pos = targetPos;
//	}
//}

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

	// 自身の列インデックスに対応する目標インデックスを取得
	formationTargetIndex = targetPlayer->GetAllyTargetIndex(formationCurrentIndex);
	// 自身の目標インデックスに対応する目標座標を取得
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(formationTargetIndex);

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
			if (targetPlayer->TryReserveFormationIndex(formationTargetIndex))
			{
				// 自身のインデックス更新
				formationCurrentIndex = formationTargetIndex;
			}
		}

		return;
	}
	// 列に加わっている場合 ※２ ※３
	else
	{
		if (!targetPlayer->IsMoving() && !targetPlayer->IsExistFrontAlly(formationCurrentIndex))
		{
			formationOffsetFrames++;
		}
		else
		{
			formationOffsetFrames = 0;
		}
	}

	trans.pos = targetPos;
}

void PlayerAlly::UpdateDebugColor()
{
	// 列に加わっていない場合は青色にする
	if (formationCurrentIndex == -1)
	{
		model->model->Getter_Appearance(0)->color = { 0,0,255,255 };
	}
	// 列に加わっている場合は緑色にする
	else
	{
		model->model->Getter_Appearance(0)->color = { 0,255,0,255 };
	}
	// 詰め移動中は黄色にする
	if (formationTargetIndex < formationCurrentIndex)
	{
		model->model->Getter_Appearance(0)->color = { 255,255,0,255 };
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