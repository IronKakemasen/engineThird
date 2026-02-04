#include "PlayerTower.h"
#include "../Json/Json.h"
#include "imgui.h"
#include "../../../Config/InGameConfig.h"
#include "../../../GameObjects/Enemy/Enemy.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../../GameObjects/InGameController/InGameController.h"
#include "../../../Systems/DamageDisplay/DamageDisplay.h"

//
PlayerTower::PlayerTower()
{
	// モデルのインスタンス化
	model.reset(new PlayerTowerModel);
	circleModel.reset(new CircleModel);
	circleModel->defaultScale = { 9.0f,1,9.0f };
	auto* c = circleModel->model->GetAppearance(0);

	c->color = { 150,150,255,255 };

	// HPバーのスプライト初期化
	HPBarBackSprite = std::make_unique<Sprite>();
	HPBarBackSprite->Initialize(100.0f, 16.0f, { },
		M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2),
		{ 0,0,0,255 });

	HPBarSprite = std::make_unique<Sprite>();
	HPBarSprite->Initialize(94.0f, 14.0f, { },
		M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2),
		{ 0,167,219,255 });

	// Jsonパスの設定
	path = "./resource/application/json/player/playerTowerData.json";
}

// リセット処理(ステージ切り替え毎に呼び出す)
void PlayerTower::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 現在選択されているステージ
	ReplaceOnMap(inGameController->curStage);
}

// マップに配置
void PlayerTower::ReplaceOnMap(const int32_t stage)
{
	// 現在選択されているステージでのアクティブ数を取得
	Json::LoadParam(path, "/stage" + std::to_string(stage) + "/ActiveCount", stageActiveCounts);
	tempStageNumber = stage;

	// ステージ毎アクティブ数とIDを比較してアクティブ化・非アクティブ化を決定
	if (stageActiveCounts > ID)
	{
		// アクティブ化
		status = Status::kActive;
		// 衝突判定をするかどうか定める
		SwitchCollisionActivation(true);
		// データ読み込み
		LoadData();
	}
	else
	{
		// 非アクティブ化
		status = Status::kInActive;
		// 衝突判定をするかどうか定める
		SwitchCollisionActivation(false);
	}
}

// 初期化処理
void PlayerTower::Init()
{
	// モデルの初期化
	model->Init(&trans);
	circleModel->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerTower);
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerTowerCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
}

// コリジョンバックテーブル設定
void PlayerTower::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

// データ保存・読み込み
void PlayerTower::LoadData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(tempStageNumber) + "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);

	/// config反映
	// HP反映
	hp = inGameConfig->playerTowerMaxHP;
}
void PlayerTower::SaveData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

// 更新処理
void PlayerTower::Update()
{
	//モデルの更新処理
	model->Update(int(currentAnimationState), animationCounter.count);
	circleModel->Update();

	UpdateAnimationState();

#ifdef _DEBUG
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerTowerCollisonSize);
#endif // _DEBUG
}

// アニメーション更新
void PlayerTower::UpdateAnimationState()
{
	// 状態が変化したらカウンター初期化
	if (nextAnimationState != currentAnimationState)
	{
		switch (nextAnimationState)
		{
		case EnemyTowerAnimationState::kIdle:
			animationCounter.Initialize(5.0f);
			break;
		case EnemyTowerAnimationState::kDamage:
			animationCounter.Initialize(0.3f);
			break;
		case EnemyTowerAnimationState::kDead:
			animationCounter.Initialize(0.1f);
			break;
		}
		currentAnimationState = nextAnimationState;
	}

	// カウンター更新
	animationCounter.Add();

	if (animationCounter.count >= 1.0f)
	{
		switch (currentAnimationState)
		{
		case EnemyTowerAnimationState::kIdle:
			nextAnimationState = EnemyTowerAnimationState::kIdle;
			break;
		case EnemyTowerAnimationState::kDamage:
			nextAnimationState = EnemyTowerAnimationState::kIdle;
			break;
		case EnemyTowerAnimationState::kDead:
			SetStatus(Status::kInActive);
			break;
		default:
			break;
		}
	}
}

// 描画処理
void PlayerTower::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
	circleModel->Draw(vpMat_);

}
void PlayerTower::DrawHpBar(Matrix4* vpMat_)
{
	if (status == Status::kInActive) return;
	if (hp >= inGameConfig->playerTowerMaxHP - 0.1f) return;

	Matrix4 orth = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
	Vector2 pos = ConvertToScreen(trans.GetWorldPos(), *vpMat_);

	HPBarBackSprite->GetAppearance()->trans.pos = Vector3(pos.x, pos.y + 30.0f, 0.0f);
	HPBarBackSprite->Draw(&orth);
	HPBarSprite->GetAppearance()->trans.pos = Vector3(pos.x, pos.y + 30.0f, 0.0f);
	float const len = 100.0f;
	float hpRate = hp / inGameConfig->playerTowerMaxHP;

	HPBarSprite->rightTop.position.x = HPBarSprite->leftTop.position.x + hpRate * len;
	HPBarSprite->rightBottom.position.x = HPBarSprite->leftBottom.position.x + hpRate * len;;

	HPBarSprite->Draw(&orth);
}

void PlayerTower::DebugDraw()
{
#ifdef USE_IMGUI

	if (status == Status::kInActive) return;

	std::string key = "##" + std::to_string(ID);

	ImGui::PushItemWidth(100.0f);
	ImGui::DragFloat((key + "position.x").c_str(), &trans.pos.x, 0.1f);
	ImGui::SameLine();
	ImGui::DragFloat((key + "position.z").c_str(), &trans.pos.z, 0.1f);
	if (ImGui::Button((std::to_string(ID) + ":Save").c_str()))
	{
		SaveData();
	}
	ImGui::SameLine();
	if (ImGui::Button((std::to_string(ID) + ":Load").c_str()))
	{
		LoadData();
	}
	ImGui::SameLine();
	if (ImGui::Button((std::to_string(ID) + ":Reset").c_str()))
	{
		Reset();
	}

#endif // USE_IMGUI
}

// Enemyとの衝突
void PlayerTower::CollisionBackToEnemy::operator()()
{
	auto* enemy = reinterpret_cast<Enemy*>(me->Getter_ColObj());

	// 既に死んでいるなら何もしない
	if (me->hp <= 0.0f) return;

	// 状態をダメージに変更
	me->nextAnimationState = PlayerTower::EnemyTowerAnimationState::kDamage;

	float power = enemy->GetAttackPower();

	float scale = 1.0f;
	int stage =int(power) % 10;
	if (stage >= 5)
	{
		scale = 1.5f;
	}
	else if (stage >= 2)
	{
		scale = 1.2f;
	}

	// 音
	AudioPlayer::GetInstance().PlayAudio(AudioHandle::Get(AudioID::PlayerTowerDamage), false, 5);

	// 
	Vector3 pos = me->Getter_Trans()->GetWorldPos();
	pos.x += (rand() % 1000 / 1000.0f - 0.5f) * 2.0f;
	pos.z += (rand() % 1000 / 1000.0f - 0.5f) * 2.0f;

	// ダメージ表示
	DamageDisplay::Get()->Activate(power, pos, scale, { 255,255,0 });

	me->hp = me->hp - power;
	if (me->hp <= 0.0f)
	{
		// 状態をデッドに変更
		me->nextAnimationState = PlayerTower::EnemyTowerAnimationState::kDead;
	}
}
