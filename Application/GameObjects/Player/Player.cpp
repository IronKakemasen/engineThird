#include "Player.h"
#include "imgui.h"
#include "../Json/Json.h"

Player::Player()
{
	// モデルのインスタンス化
	model.reset(new PlayerModel);
}

void Player::Reset()
{
	// モデルのリセット
	model->Reset();

	// allyExistenceFlagsの初期化
	allyExistenceFlags.fill(false);
	// posHistoryの初期化
	posHistory.fill(Vector3(0.0f, 0.0f, 0.0f));
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

	// Jsonからデータをロード
	//Json::Load("./resource/json/player/playerData.json");
	//Json::Load("./resource/json/player/playerData.json", "position", trans.pos);
	//Json::Load("./resource/json/player/playerData.json", "velocity", velocity);
}

void Player::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

void Player::Update()
{
	//モデルの更新処理
	model->Update();

	Move();

	SavePos();
}

void Player::Draw(Matrix4 * vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

// Enemyとの衝突
void Player::CollisionBackToEnemy::operator()()
{
	// 自身の取得
	auto* player = me;
	me->trans.rotation.y += 1.0f;
}



void Player::Move()
{
	isMoving = false;

	// 移動方向ベクトル
	Vector3 moveDir = Vector3(0.0f, 0.0f, 0.0f);

	if (M::GetInstance()->getPadState.GetConnectedPadNum() > 0)
	{
		// 左スティックの入力を取得
		Vector2 leftStick = M::GetInstance()->getPadState.GetLeftStick(0);
		moveDir.x -= leftStick.x;
		moveDir.z += leftStick.y;
	}
	else
	{
		if (M::GetInstance()->IsKeyPressed(KeyType::W)) moveDir.z += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::S)) moveDir.z -= 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::D)) moveDir.x += 1.0f;
		if (M::GetInstance()->IsKeyPressed(KeyType::A)) moveDir.x -= 1.0f;
	}

	// 正規化
	moveDir.GetNormalized();

	if (moveDir.x != 0.0f || moveDir.z != 0.0f)isMoving = true;

	trans.pos = trans.pos + moveDir * GameConstants::kPlayerSpeed;
}

void Player::SavePos()
{
	// 味方の存在フラグをリセット
	emptyAllyIndex = 0;

	if (!isMoving)return;

	// 座標履歴を保存
	posHistory[headIndex] = trans.pos;
	headIndex++;
	if (headIndex >= posHistory.size()) { headIndex = 0; }
}

Vector3 Player::GetAllyTargetPos(size_t allyIndex)
{
	size_t index = headIndex + (allyIndex + 1) * GameConstants::kAllyFollowDelayFrames;
	return posHistory[index % posHistory.size()];
}

uint32_t Player::GetNextEmptyAllyIndex()
{
	return emptyAllyIndex++;
}

void Player::SaveData()
{
	//Json::AddParam("./resource/json/player/playerData.json", "position", trans.pos);
	//Json::AddParam("./resource/json/player/playerData.json", "velocity", velocity);
	//Json::Save("./resource/json/player/playerData.json");
}