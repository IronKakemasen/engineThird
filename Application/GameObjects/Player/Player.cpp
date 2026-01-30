#include "Player.h"
#include "imgui.h"
#include "../Json/Json.h"
#include "../../../M/lowerLayer/engineCore/Light/RectLight/RectLight.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../Config/InGameConfig.h"
#include "../../Config/GameConstants.h"

#include <algorithm>
#include <numeric>

Player::Player()
{

	// モデルのインスタンス化
	model.reset(new PlayerModel);	

	// Jsonパスの設定
	path = "./resource/application/json/player/playerData.json";
}

void Player::Reset()
{
	// モデルのリセット
	model->Reset();

	// existの初期化
	exist.fill(false);
	// formedAllyCountの初期化
	formedAllyCount = 0;
	// unformedAllyCountの初期化
	unformedAllyCount = 0;
	// delayFrameOffsetsの初期化
	delayFrameOffsets = 0;
	// posHistoryの初期化
	posHistory.fill(trans.pos);
	// headIndexの初期化
	headIndex = 0;

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// データ読み込み
	LoadData();

	// カウンター初期化
	autoSpawnAllyCounter.Initialize(inGameConfig->playerAllySpawnInterval);
	attackIntervalCounter.Initialize(inGameConfig->playerAttackInterval);
}

void Player::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayer);
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	//inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);


	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
}

void Player::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

void Player::SpawnAlly(Vector3 pos)
{
	for (auto* ally : allies)
	{
		if (ally->GetStatus() == GameObjectBehavior::Status::kInActive)
		{
			// 配置
			ally->Spawn(pos);
			break;
		}
	}
}


// データ保存・読み込み
void Player::LoadData()
{
	// config反映
	hp = inGameConfig->playerMaxHP;
}
void Player::SaveData()
{
}

// 更新処理
void Player::Update()
{
	//モデルの更新処理
	model->Update();

	// 移動処理
	Move();

	// 座標保存処理
	SavePos();

	// 視線変更処理
	UpdateLookDir();

	// 味方データ更新処理
	UpdateAllyData();

	// 攻撃処理
	Attack();

	// 味方自動補充処理
	AutoSpawnAlly();

#ifdef _DEBUG
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerCollisonSize);
#endif // _DEBUG
}

// 描画処理
void Player::Draw(Matrix4 * vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void Player::DebugDraw()
{
#ifdef USE_IMGUI

	//ImGui::Text("---------------------------------------------\n");
	//
	//for (size_t i = 0; i < 10; i++)
	//{
	//	if (exist[i])
	//	{
	//		ImGui::Text("%d:#\n", i);
	//	}
	//	else
	//	{
	//		ImGui::Text("%d: \n", i);
	//	}
	//}
	//ImGui::Text("formedAllyCount:%d\n", formedAllyCount);
	//
	//for (size_t i = 0; i < deadIndexList.size(); i++)
	//{
	//	ImGui::Text("deadIndexList[%d]:%d\n", i, deadIndexList.front());
	//}
	//ImGui::Text("delayFrameOffsets:%d\n", delayFrameOffsets);
	//
	//for (size_t i = 0; i < 10; i++)
	//{
	//	if (ImGui::Button(("remove##" + std::to_string(i)).c_str()))
	//	{
	//		for (auto& ally : allies)
	//		{
	//			if (ally->GetStatus() == GameObjectBehavior::Status::kActive && ally->formationCurrentIndex == i)
	//			{
	//				ally->Death();
	//				break;
	//			}
	//		}
	//	}
	//}

#endif // USE_IMGUI
}


// Enemyとの衝突処理
void Player::CollisionBackToEnemy::operator()()
{
	// 自身の取得
	auto* player = me;
	me->trans.rotation.y += 1.0f;
}


// 移動処理
void Player::Move()
{
	// 移動方向ベクトル
	Vector3 moveDir = Vector3(0.0f, 0.0f, 0.0f);
	// 移動フラグ初期化
	isMoving = false;

	bool left = M::GetInstance()->getPadState.IsHeld(0, PAD_LEFT);
	bool right = M::GetInstance()->getPadState.IsHeld(0, PAD_RIGHT);
	bool up = M::GetInstance()->getPadState.IsHeld(0, PAD_UP);
	bool down = M::GetInstance()->getPadState.IsHeld(0, PAD_DOWN);
	if (!left && !right && !up && !down)
	{
		// 十字キーの入力がない場合はスティック入力を使う
		// 左スティックの入力を取得
		Vector2 leftStick = M::GetInstance()->getPadState.GetLeftStick(0);
		if (leftStick.x < 0.2f && leftStick.x > -0.2f) leftStick.x = 0.0f;
		if (leftStick.y < 0.2f && leftStick.y > -0.2f) leftStick.y = 0.0f;
		moveDir.x += leftStick.x;
		moveDir.z += leftStick.y;
	}
	else
	{
		if (left) moveDir.x -= 1.0f;
		if (right) moveDir.x += 1.0f;
		if (up) moveDir.z += 1.0f;
		if (down) moveDir.z -= 1.0f;
	}

#ifdef _DEBUG

	if (M::GetInstance()->IsKeyPressed(KeyType::A)) moveDir.x -= 1.0f;
	if (M::GetInstance()->IsKeyPressed(KeyType::D)) moveDir.x += 1.0f;
	if (M::GetInstance()->IsKeyPressed(KeyType::W)) moveDir.z += 1.0f;
	if (M::GetInstance()->IsKeyPressed(KeyType::S)) moveDir.z -= 1.0f;

#endif // _DEBUG

	// 正規化
	moveDir = moveDir.GetNormalized();

	// 移動判定
	if (moveDir.x != 0.0f || moveDir.z != 0.0f)isMoving = true;

	// 移動処理
	trans.pos = trans.pos + moveDir * inGameConfig->playerSpeed;

	// 画面外に出ないようにクランプ
	ClampPosition(trans.pos);

	//まんてじゃみ追加事項
	deltaPos = moveDir * inGameConfig->playerSpeed;
}

// 攻撃処理
void Player::Attack()
{
	// 攻撃間隔カウンター更新
	attackIntervalCounter.Add();
	if (attackIntervalCounter.count < 1.0f) return;

	if (M::GetInstance()->getPadState.IsHeld(0, PAD_RB))
	{
		for (auto* bullet : bullets)
		{
			if (bullet->GetStatus() == GameObjectBehavior::Status::kInActive)
			{
				// カウンター初期化
				attackIntervalCounter.Initialize(inGameConfig->playerAttackInterval);

				// 発射
				bullet->Fire(trans.pos, trans.lookDir);

				break;
			}
		}
	}

#ifdef _DEBUG
	if (M::GetInstance()->IsKeyPressed(KeyType::SPACE))
	{
		for (auto* bullet : bullets)
		{
			if (bullet->GetStatus() == GameObjectBehavior::Status::kInActive)
			{
				// カウンター初期化
				attackIntervalCounter.Initialize(inGameConfig->playerAttackInterval);

				// 発射
				bullet->Fire(trans.pos, trans.lookDir);

				break;
			}
		}
	}
#endif // _DEBUG
}

// 座標保存処理
void Player::SavePos()
{
	if (!isMoving)return;

	// 座標履歴を保存
	posHistory[headIndex] = trans.pos;
	headIndex++;
	if (headIndex >= posHistory.size()) { headIndex = 0; }
}
// プレイヤーのnフレーム前の座標を取得
Vector3 Player::GetPosHistory(int32_t n)
{
	// 座標履歴のインデックス
	int32_t index = (static_cast<int32_t>(headIndex) - n - 1);
	if (index < 0) index += static_cast<int32_t>(posHistory.size());
	return posHistory[index];
}

void Player::UpdateAllySeparate()
{}

// 視線変更処理
void Player::UpdateLookDir()
{
	// 視線方向ベクトル
	Vector3 target = Vector3(0.0f, 0.0f, 0.0f);

	// 右スティックの入力を取得
	Vector2 rightStick = M::GetInstance()->getPadState.GetRightStick(0);
	if (rightStick.x < 0.2f && rightStick.x > -0.2f) rightStick.x = 0.0f;
	if (rightStick.y < 0.2f && rightStick.y > -0.2f) rightStick.y = 0.0f;
	target.x = rightStick.x;
	target.z = rightStick.y;
	if (target.x == 0.0f && target.z == 0.0f) return;

	// 正規化
	trans.lookDir = target.GetNormalized();
}

// 味方自動補充処理
void Player::AutoSpawnAlly()
{
	if (formedAllyCount > inGameConfig->maxAllyCount) return;

	autoSpawnAllyCounter.Add();

	if (autoSpawnAllyCounter.count >= 1.0f)
	{
		autoSpawnAllyCounter.Initialize(inGameConfig->playerAllySpawnInterval);
		// 味方をスポ
		SpawnAlly(trans.pos);
	}
}


// 味方データ更新処理
void Player::UpdateAllyData()
{
	// 味方の数をリセット
	formedAllyCount = 0;
	unformedAllyCount = 0;

	exist.fill(false);

	// formed の ally を集める
	std::vector<PlayerAlly*> formedAllies;
	formedAllies.reserve(allies.size());

	for (int32_t i = 0; i < allies.size(); ++i)
	{
		if (allies[i]->GetStatus() == GameObjectBehavior::Status::kActive)
		{
			// 列に並んでいるなら
			if (allies[i]->GetCurrentState() == PlayerAlly::State::kFormed)
			{
				formedAllies.push_back(allies[i]);
				formedAllyCount++;
			}
			else
			{
				unformedAllyCount++;
			}
		}
	}

	// formationCurrentIndex を昇順に並べる
	std::sort(formedAllies.begin(), formedAllies.end(),
		[](const PlayerAlly* a, const PlayerAlly* b)
		{
			const int32_t ia = a ? a->formationCurrentIndex : GameConstants::kMaxAllies;
			const int32_t ib = b ? b->formationCurrentIndex : GameConstants::kMaxAllies;
			return ia < ib;
		});

	// 現在の exist を構築
	for (auto* ally : formedAllies)
	{
		exist[ally->formationCurrentIndex] = true;
		if (ally->formationCurrentIndex < 0)
		{
			// ありえない
			DebugBreak();
		}
	}

	// 列に隙間が存在するか？
	int32_t gapIndex = -1;
	for (int32_t i = 0; i < formedAllyCount; ++i)
	{
		if (!exist[i])
		{
			gapIndex = i;
			break;
		}
	}

	// 詰め作業
	if (gapIndex != -1)
	{
		delayFrameOffsets += 2;

		// 1人分詰め切ったら、論理 index も 1ステップだけ確定
		if (delayFrameOffsets >= inGameConfig->allyToAllyDelayFrames)
		{
			delayFrameOffsets = 0;

			// gapIndex より後ろの formed だけ 1つ前へ
			for (auto* ally : formedAllies)
			{
				const int32_t idx = ally->formationCurrentIndex;
				if (idx > gapIndex)
				{
					ally->formationCurrentIndex--;
				}
			}
		}
	}
	else
	{
		// 隙間がないなら詰めオフセットは不要
		delayFrameOffsets = 0;
	}
}


Vector3 Player::GetAllyTargetPos(int32_t allyIndex)
{
	int32_t index = allyIndex;
	if (index < 0) index = formedAllyCount;

	int32_t delayFrames = (index + 1) * inGameConfig->allyToAllyDelayFrames;
	delayFrames += inGameConfig->playerToAllyDelayFrames;

	int32_t offset = 0;

	// 前に空きがあれば
	for (int32_t i = 0; i < index; ++i)
	{
		if (i < 0 || i >= GameConstants::kMaxAllies) break;
		if (!exist[i])
		{
			offset = delayFrameOffsets;
			break;
		}
	}
	return GetPosHistory(delayFrames - offset);
}
int32_t Player::TryReserveFormationIndex()
{
	if (exist[formedAllyCount] == false)
	{
		exist[formedAllyCount] = true;
		return formedAllyCount;
	}
	else
	{
		return -1;
	}
}

int32_t Player::GetSeparateAllyCount() const
{
	return -1;
}

float Player::GetSpeed() const
{
	return inGameConfig->playerSpeed;
}

