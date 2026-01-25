#include "Player.h"
#include "imgui.h"
#include "../Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../Config/GameConstants.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"


Player::Player()
{
	// モデルのインスタンス化
	model.reset(new PlayerModel);

	// 必須でない
	auto* appearance = model->model->Getter_Appearance(0);
	
	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 0,255,0,255 };

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
}

void Player::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayer);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

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
	std::string key = "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
	Json::LoadParam(path, key + "/speed", speed);
}
void Player::SaveData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::SaveParam(path, key + "/speed", speed);
	Json::Save(path);
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
		if (M::GetInstance()->IsKeyPressed(KeyType::W)) moveDir.z += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::S)) moveDir.z -= 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::D)) moveDir.x += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::A)) moveDir.x -= 1.0f;
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

	trans.pos = trans.pos + moveDir * speed;
}

void Player::Attack()
{
	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		if (!M::GetInstance()->getPadState.IsJustPressed(0, PAD_RB)) return;
	}
	else
	{
		if (!M::GetInstance()->IsKeyTriggered(KeyType::SPACE)) return;
	}

	for (auto* bullet : bullets)
	{
		if (bullet->GetStatus() == GameObjectBehavior::Status::kInActive)
		{
			attackGauge -= 1.0f;
			if (attackGauge < 0.0f)
				attackGauge = 0.0f;

			int32_t stage = 0;
			if (attackGauge >= 2.0f)stage = 2;
			else if (attackGauge >= 1.0f)stage = 1;
			else stage = 0;

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
	else
	{
		if (M::GetInstance()->IsKeyPressed(KeyType::UP))	target.z += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::DOWN))	target.z -= 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::RIGHT)) target.x += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::LEFT))	target.x -= 1.0f;
	}

	if (target.x == 0.0f && target.z == 0.0f) return;

	// 正規化
	trans.lookDir = target.GetNormalized();
}

// プレイヤーのnフレーム前の座標を取得
Vector3 Player::GetPosHistory(int32_t n)
{
	// 座標履歴のインデックス
	int32_t index = (static_cast<int32_t>(headIndex) - n - 1);
	if (index < 0) index += static_cast<int32_t>(posHistory.size());
	return posHistory[index];
}

// 
// 0 - 1 - 2 - 3 - x - 5 - 6    新　新　新
// 
// 上記のように4番目の味方が抜けた場合
// currentIndex 0,1,2,3 の場合返り値はそのまま0,1,2,3
// currentIndex 4 のキャラはそもそもこの関数を呼ばない
// currentIndex 5,6 の場合返り値はそれぞれ4,5となり詰める
// currentIndex -1(新規) の場合返り値は列を完全に詰めた場合の最後尾(上記例だと6)となり最後尾を指す
// 

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
			if (delayFrameOffsets >= GameConstants::kAllyFollowDelayFrames)
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

	int32_t delayFrames = (index + 1) * GameConstants::kAllyFollowDelayFrames;
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
