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

	// allyExistenceFlagsの初期化
	allyExistenceFlags.fill(false);
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

	// 視線変更処理
	UpdateLookDir();

	// 座標保存処理
	SavePos();

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


	for (size_t i = 0; i < allyExistenceFlags.size(); i++)
	{
		if (allyExistenceFlags[i])
		{
			ImGui::Text("%d:#\n", i);
		}
		else
		{
			ImGui::Text("%d: \n", i);
		}
		ImGui::SameLine();
		std::string key = "remove##" + std::to_string(i);
		if (ImGui::Button(key.c_str()))
		{
			allies[i]->SetStatus(GameObjectBehavior::Status::kInActive);
		}
		ImGui::SameLine();
		ImGui::Text("c:%d", allies[i]->formationCurrentIndex);
		ImGui::SameLine();
		ImGui::Text("t :%d", allyTargetIndices[i]);
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


	// 毎フレーム再構築（味方側から直接いじらない）
	allyExistenceFlags.fill(false);

	for (int32_t i = 0; i < allies.size(); ++i)
	{
		// アクティブなら
		if (allies[i]->GetStatus() != GameObjectBehavior::Status::kActive) continue;


		if (allies[i]->formationCurrentIndex >= 0)
		{
			const uint32_t idx = static_cast<uint32_t>(allies[i]->formationCurrentIndex);
			if (idx < allyExistenceFlags.size())
			{
				allyExistenceFlags[idx] = true;
				formedAllyCount++;
			}
		}
		else
		{
			unformedAllyCount++;
		}
	}

	// 「穴が空いたら詰める」用マッピングを作る
	uint32_t empty = 0;
	for (uint32_t i = 0; i < GameConstants::kMaxAllies; ++i)
	{
		allyTargetIndices[i] = i - empty;

		if (!allyExistenceFlags[i])
		{
			empty++;
		}
	}
	//// 味方の存在フラグを更新
	//uint32_t fakeSum = 0;
	//for (size_t i = 0; i < allyExistenceFlags.size(); ++i)
	//{
	//	if (allyExistenceFlags[i] == true)
	//	{
	//		// 見かけ上の人数
	//		fakeSum++;
	//		// 実際に並んでいる人数
	//		if (allies[i]->GetStatus() == GameObjectBehavior::Status::kActive)
	//		{
	//			formedAllyCount++;
	//		}
	//	}
	//}
	//
	////// fakeSum != formedAllyCount の場合、allyExistenceFlagsの後半のtrueは誤りなのでfalseにする
	////if (fakeSum != formedAllyCount)
	////{
	////	for (size_t i = 0; i < allyExistenceFlags.size(); ++i)
	////	{
	////		if (fakeSum > formedAllyCount && allyExistenceFlags[i] == true)
	////		{
	////			allyExistenceFlags[i] = false;
	////			//fakeSum--;
	////		}
	////	}
	////}
	//
	//uint32_t empty = 0;
	//for (uint32_t i = 0; i < GameConstants::kMaxAllies; ++i)
	//{
	//	allyTargetIndices[i] = i - empty;
	//
	//	if (!allyExistenceFlags[i])
	//	{
	//		empty++;
	//	}
	//}
}
// 味方の目標座標を取得
Vector3 Player::GetAllyTargetPos(int32_t allyIndex)
{
	// ※１
	// そもそも列に並んでいない 場合
	// 目標座標は最後尾+1の座標

	// ※２
	// 前に味方がいる && (isMovingNow || !isMovingNow) の場合
	// 目標座標は通常通り遅延フレーム*列index前の座標

	// ※３
	// 前に味方がいない && isMovingNow の場合
	// 目標座標は通常通り遅延フレーム*列index前の座標
	// 詰めたいが、座標履歴に完璧に追従する場合は速度が急激にあがるため詰めれない
	// 速度は変えず、最短経路を通り詰める方式はそもそもゲーム性が変わるため採用しない

	// ※４
	// 前に味方がいない && !isMovingNow の場合
	// 目標座標は通常目指す座標よりstopMoveFrameだけ前に詰めた座標
	// 例：stopMoveFrameが5フレームの場合、通常目指す座標より5フレーム前の座標を目標座標とする
	// これにより味方の速度がどんな時も変わらず、かつ見た目の説得力も保てる
	
	// 前に味方いるか
	bool isExistFrontAlly = IsExistFrontAlly(allyIndex);
	// 現在動いているか(いらないが可読性向上のため記述)
	bool isMovingNow = isMoving;
	// 列に並んでいるか
	bool isFormed = (allyIndex != -1);
	// プレイヤーから何フレーム遅れの位置か
	int32_t delayFrames = (allyIndex + 1) * GameConstants::kAllyFollowDelayFrames;
	// 座標履歴のインデックス
	int32_t index = (static_cast<int32_t>(headIndex) - delayFrames);
	if (index < 0) index += static_cast<int32_t>(posHistory.size()); 
	// 理想的な位置
	Vector3 idealPos = posHistory[index];


	// ※１ そもそも列に並んでいない 場合
	if (!isFormed)
	{
		// 目標座標は最後尾+1の座標
		int32_t adjustedIndex = index;
		adjustedIndex = adjustedIndex - (formedAllyCount * GameConstants::kAllyFollowDelayFrames);
		if (adjustedIndex < 0) adjustedIndex += static_cast<int32_t>(posHistory.size());
		return posHistory[adjustedIndex];
	}

	// ※２ 前に味方がいる && (isMovingNow || !isMovingNow) の場合
	if (isExistFrontAlly)
	{
		return idealPos;
	}

	// ※３ 前に味方がいない && isMovingNow の場合
	if (!isExistFrontAlly && isMovingNow)
	{
		return idealPos;
	}

	// ※４ 前に味方がいない && !isMovingNow の場合
	if (!isExistFrontAlly && !isMovingNow)
	{
		// stopMoveFrame分前に詰めた座標を返す
		int32_t adjustedIndex = index;
		adjustedIndex = adjustedIndex - allies[allyIndex]->formationOffsetFrames;
		if (adjustedIndex < 0) adjustedIndex += static_cast<int32_t>(posHistory.size());
		return posHistory[adjustedIndex];
	}

	return idealPos;
}
int32_t Player::GetAllyTargetIndex(int32_t currentIndex)
{
	// 新規の場合、最後尾を返す
	if (currentIndex == -1)
	{
		return formedAllyCount;
	}

	return allyTargetIndices[currentIndex];
}
bool Player::TryReserveFormationIndex(int32_t preferredIndex)
{
	if (allyExistenceFlags[preferredIndex] == false)
	{
		allyExistenceFlags[preferredIndex] = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool Player::IsExistFrontAlly(int32_t currentIndex)
{
	if (currentIndex <= 0) { return true; }

	if (allyExistenceFlags[currentIndex - 1])
	{
		return true;
	}
	return false;
}
