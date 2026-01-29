#include "Player.h"
#include "imgui.h"
#include "../Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../Config/GameConstants.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../Config/InGameConfig.h"
#include "../../../M/lowerLayer/engineCore/Light/RectLight/RectLight.h"

Player::Player()
{
	rectLight = M::GetInstance()->ImportRectLight();
	auto* para = rectLight->Getter_Para();
	para->isActive = 0;

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
	// deadIndexListの初期化
	while (!deadIndexList.empty())
	{
		deadIndexList.pop_back();
	}
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

	autoSpawnAllyCounter.Initialize(inGameConfig->playerAllySpawnInterval);
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
	LightFollowPlayer();

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

	static std::vector<float> values(100, 0.0f);
	static int index = 0;

	values[index] = attackGauge;
	index = (index + 1) % values.size();

	ImGui::PlotLines("AttackGauge", values.data(), int(values.size()), index, nullptr, 0.0f, 3.0f, ImVec2(0, 80));

	ImGui::Text("---------------------------------------------\n");

	float arr[1] = { attackGauge };
	ImGui::PlotHistogram("Gauge", arr, 1, 0, nullptr, 0.0f, 3.0f, ImVec2(0, 80));

	ImGui::Text("---------------------------------------------\n");

	ImDrawList* draw = ImGui::GetWindowDrawList();
	ImVec2 center = ImGui::GetCursorScreenPos();
	center.x += 50;
	center.y += 50;

	float radius = 40.0f;
	float value = attackGauge / 3.0f;

	draw->PathArcTo(center, radius, -3.1415f / 2.0f, -3.1415f / 2.0f + 3.1415f * 2.0f * value, 32);
	draw->PathStroke(IM_COL32(0, 255, 0, 255), false, 6.0f);

	ImGui::Text("---------------------------------------------\n");

	for (size_t i = 0; i < 10; i++)
	{
		if (exist[i])
		{
			ImGui::Text("%d:#\n", i);
		}
		else
		{
			ImGui::Text("%d: \n", i);
		}
	}
	ImGui::Text("formedAllyCount:%d\n", formedAllyCount);

	for (size_t i = 0; i < deadIndexList.size(); i++)
	{
		ImGui::Text("deadIndexList[%d]:%d\n", i, deadIndexList.front());
	}
	ImGui::Text("delayFrameOffsets:%d\n", delayFrameOffsets);

	for (size_t i = 0; i < 10; i++)
	{
		if (ImGui::Button(("remove##" + std::to_string(i)).c_str()))
		{
			for (auto& ally : allies)
			{
				if (ally->GetStatus() == GameObjectBehavior::Status::kActive && ally->formationCurrentIndex == i)
				{
					ally->Death();
					break;
				}
			}
		}
	}

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
	isMoving = false;

	// 移動方向ベクトル
	Vector3 moveDir = Vector3(0.0f, 0.0f, 0.0f);

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
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
	}
	else
	{
		auto* m = M::GetInstance();

		if (m ->IsKeyPressed(KeyType::A)) moveDir.x -= 1.0f;
		if (m ->IsKeyPressed(KeyType::D)) moveDir.x += 1.0f;
		if (m ->IsKeyPressed(KeyType::W)) moveDir.z += 1.0f;
		if (m ->IsKeyPressed(KeyType::S)) moveDir.z -= 1.0f;
	}

	// 正規化
	moveDir = moveDir.GetNormalized();

	if (moveDir.x != 0.0f || moveDir.z != 0.0f)
	{
		isMoving = true;
		//stopMoveFrame = 0;
	}
	else
	{
		//stopMoveFrame++;
	}

	trans.pos = trans.pos + moveDir * inGameConfig->playerSpeed;


	ClampPosition(trans.pos);

	//まんてじゃみ追加事項
	deltaPos = moveDir * inGameConfig->playerSpeed;
}

void Player::Attack()
{
	// 攻撃間隔カウンター更新
	attackIntervalCounter.Add();
	if (attackIntervalCounter.count >= 1.0f)
	{
		// 攻撃間隔経過後はゲージ回復
		attackGauge += inGameConfig->playerAttackGaugeRecoverSpeed;
		if (attackGauge > 3.0f)
			attackGauge = 3.0f;
	}


	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		if (!M::GetInstance()->getPadState.IsJustPressed(0, PAD_RB)) return;
	}
	else
	{
		if (!M::GetInstance()->IsKeyTriggered(KeyType::SPACE)) return;
	}

	if (attackGauge < 1.0f)return;

	for (auto* bullet : bullets)
	{
		if (bullet->GetStatus() == GameObjectBehavior::Status::kInActive)
		{
			attackGauge -= 1.0f;
			if (attackGauge < 0.0f)
				attackGauge = 0.0f;

			int32_t stage = 0;
			if (attackGauge >= 2.0f)stage = 0;
			else if (attackGauge >= 1.0f)stage = 1;
			else stage = 2;

			attackIntervalCounter.Initialize(inGameConfig->playerAttackGaugeRecoverInterval);

			// リセット
			bullet->Fire(trans.pos, trans.lookDir, stage);

			break;
		}
	}
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

// 視線変更処理
void Player::UpdateLookDir()
{
	// 視線方向ベクトル
	Vector3 target = Vector3(0.0f, 0.0f, 0.0f);

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		// 右スティックの入力を取得
		Vector2 rightStick = M::GetInstance()->getPadState.GetRightStick(0);
		if (rightStick.x < 0.2f && rightStick.x > -0.2f) rightStick.x = 0.0f;
		if (rightStick.y < 0.2f && rightStick.y > -0.2f) rightStick.y = 0.0f;
		target.x = rightStick.x;
		target.z = rightStick.y;
	}

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

// プレイヤーのnフレーム前の座標を取得
Vector3 Player::GetPosHistory(int32_t n)
{
	// 座標履歴のインデックス
	int32_t index = (static_cast<int32_t>(headIndex) - n - 1);
	if (index < 0) index += static_cast<int32_t>(posHistory.size());
	return posHistory[index];
}

// 味方データ更新処理
void Player::UpdateAllyData()
{
	// 味方の数をリセット
	formedAllyCount = 0;
	unformedAllyCount = 0;

	exist.fill(false);

	for (int32_t i = 0; i < allies.size(); ++i)
	{
		if (allies[i]->GetStatus() == GameObjectBehavior::Status::kActive)
		{
			// 列に並んでいるなら
			if (allies[i]->formationCurrentIndex >= 0)
			{
				exist[allies[i]->formationCurrentIndex] = true;
				formedAllyCount++;
			}
			else
			{
				unformedAllyCount++;
			}
		}
	}

	// 詰めオフセット更新
	if (!deadIndexList.empty())
	{
		if (!isMoving)
		{
			delayFrameOffsets++;
			if (delayFrameOffsets >= inGameConfig->allyToAllyDelayFrames)
			{
				// オフセットリセット
				delayFrameOffsets = 0;
				// 詰め終わったので存在フラグを更新
				for (size_t i = deadIndexList.front(); i < exist.size() - 1; ++i)
				{
					exist[i] = exist[i + 1];
				}
				exist[exist.size() - 1] = false;
				// 味方の列インデックスを詰める
				for (auto* ally : allies)
				{
					if (ally->formationCurrentIndex > deadIndexList.front())
					{
						ally->formationCurrentIndex--;
					}
				}
				// deadIndexList更新
				for (size_t i = 0; i < deadIndexList.size(); ++i)
				{
					if (deadIndexList[i] > deadIndexList.front())
					{
						deadIndexList[i]--;
					}
				}
				// 次の味方へ
				deadIndexList.pop_front();
			}
		}
		else
		{
			// 動いている場合はオフセットリセット
			delayFrameOffsets = 0;
		}
	}
}


Vector3 Player::GetAllyTargetPos(int32_t allyIndex)
{
	int32_t index = allyIndex;
	if (index < 0)
	{
		index = formedAllyCount;
	}

	int32_t delayFrames = (index + 1) * inGameConfig->allyToAllyDelayFrames;
	delayFrames += inGameConfig->playerToAllyDelayFrames;
	int32_t offset = 0;
	if (!deadIndexList.empty() && index >= deadIndexList.front())
	{
		offset = delayFrameOffsets;
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

void Player::NotifyAllyDeath(int32_t formationIndex)
{
	deadIndexList.push_back(formationIndex);
}

float Player::GetSpeed() const
{
	return inGameConfig->playerSpeed;
}

void Player::LightFollowPlayer()
{
	auto* para = rectLight->Getter_Para();
	para->pos = trans.GetWorldPos();
	para->pos.z -= 2.0f;
}