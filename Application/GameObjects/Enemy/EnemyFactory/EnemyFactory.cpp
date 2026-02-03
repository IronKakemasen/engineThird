#include "EnemyFactory.h"
#include "../Json/Json.h"
#include "imgui.h"
#include "../../../Config/GameConstants.h"
#include "../../../Config/InGameConfig.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../Enemy/Enemy.h"
#include "../../InGameController/InGameController.h"
#include "../../../Systems/DamageDisplay/DamageDisplay.h"

// 
EnemyFactory::EnemyFactory()
{
	//モデルのインスタンス化
	model.reset(new EnemyFactoryModel);
	circleModel.reset(new CircleModel);
	circleModel->defaultScale = { 9.0f,1,9.0f };
	auto* c = circleModel->model->GetAppearance(0);

	c->color = { 255,200,200,255 };

	// Jsonパスの設定
	path = "./resource/application/json/enemy/enemyFactoryData.json";
}

// リセット処理(ステージ切り替え毎に呼び出す)
void EnemyFactory::Reset()
{
	// モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// 現在選択されているステージ
	ReplaceOnMap(inGameController->curStage);

	nextAnimationState = EnemyFactoryAnimationState::kIdle;
}

// マップに配置
void EnemyFactory::ReplaceOnMap(const int32_t stage)
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
void EnemyFactory::Init()
{
	// モデルの初期化
	model->Init(&trans);
	circleModel->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	SetIdentity(Tag::kEnemyFactory);
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->enemyFactoryCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);
	// エネミーポインタ取得
	for (auto& towerObj : gameObjectManager->Find(Tag::kEnemy))
	{
		enemies.push_back(reinterpret_cast<Enemy*>(towerObj));
	}

	// collisionBackToPlayerBulletの初期化
	collisionBackToPlayerBullet.Init(this);
}

// コリジョンバックテーブル設定
void EnemyFactory::SetCollisionBackTable()
{
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
}

// データ保存・読み込み
void EnemyFactory::LoadData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(tempStageNumber) + "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);

	/// config反映
	// HP設定
	hp = inGameConfig->enemyFactoryMaxHP;

	spawnCounter.Initialize(inGameConfig->enemySpawnInterval);
}
void EnemyFactory::SaveData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

// 更新処理
void EnemyFactory::Update()
{
	model->Update(int(currentAnimationState), animationCounter.count);

	circleModel->Update();

	// アニメーション更新
	UpdateAnimationState();

	// 衝突弾リスト更新
	UpdateHitBullets();

	// スポーン処理
	SpawnEnemy();


#ifdef _DEBUG
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->enemyFactoryCollisonSize);
#endif // _DEBUG
}

// アニメーション更新
void EnemyFactory::UpdateAnimationState()
{
	// 状態が変化したらカウンター初期化
	if (nextAnimationState != currentAnimationState)
	{
		switch (nextAnimationState)
		{
		case EnemyFactoryAnimationState::kIdle:
			animationCounter.Initialize(1.0f);
			break;
		case EnemyFactoryAnimationState::kDamage:
			animationCounter.Initialize(0.2f);
			break;
		case EnemyFactoryAnimationState::kGenerate:
			animationCounter.Initialize(1.0f);
			break;
		case EnemyFactoryAnimationState::kDead:
			animationCounter.Initialize(1.0f);
			break;
		default:
			break;
		}
		currentAnimationState = nextAnimationState;
	}

	animationCounter.Add();

	if (animationCounter.count >= 1.0f)
	{
		switch (currentAnimationState)
		{
		case EnemyFactory::EnemyFactoryAnimationState::kIdle:
			nextAnimationState = EnemyFactoryAnimationState::kIdle;
			break;
		case EnemyFactory::EnemyFactoryAnimationState::kDamage:
			nextAnimationState = EnemyFactoryAnimationState::kIdle;	
			break;
		case EnemyFactory::EnemyFactoryAnimationState::kGenerate:
			nextAnimationState = EnemyFactoryAnimationState::kIdle;
			break;
		case EnemyFactory::EnemyFactoryAnimationState::kDead:
			SetStatus(Status::kInActive);
			break;
		default:
			break;
		}
	}
}


// 衝突した弾をリストに追加
void EnemyFactory::AddHitBullet(PlayerBullet* bullet)
{
	hitBullets.push_back(bullet);
}
// その弾が既に衝突リストにあるか
bool EnemyFactory::IsInHitBulletList(PlayerBullet* bullet)
{
	for (auto& hitBullet : hitBullets)
	{
		if (hitBullet == bullet)
		{
			return true;
		}
	}
	return false;
}
// 衝突弾リスト更新
void EnemyFactory::UpdateHitBullets()
{
	for (size_t i = 0; i < hitBullets.size(); ++i)
	{
		if (hitBullets[i]->GetStatus() == Status::kInActive)
		{
			hitBullets.erase(hitBullets.begin() + i);
			--i;
		}
	}
}

// エネミー生産
void EnemyFactory::SpawnEnemy()
{
	spawnCounter.Add();
	if (spawnCounter.IsEnd())
	{
		for (auto& enemy : enemies)
		{
			if (enemy->GetStatus() == Status::kInActive)
			{
				enemy->Spawn(trans.pos);
				nextAnimationState = EnemyFactoryAnimationState::kGenerate;
				spawnCounter.Initialize(inGameConfig->enemySpawnInterval);
				break;
			}
		}
	}
}

void EnemyFactory::Draw(Matrix4 * vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
	circleModel->Draw(vpMat_);

}

void EnemyFactory::DebugDraw()
{
#ifdef USE_IMGUI
	
	if (status == Status::kInActive) return;

	std::string key = "##" + std::to_string(ID);

	ImGui::PushItemWidth(100.0f);
	ImGui::DragFloat((key + "position.x").c_str(), &trans.pos.x, 0.1f);
	ImGui::SameLine();
	ImGui::PushItemWidth(100.0f);
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

// プレイヤー弾との衝突
void EnemyFactory::CollisionBackToPlayerBullet::operator()()
{
	auto* playerBullet = reinterpret_cast<PlayerBullet*>(me->Getter_ColObj());

	// 既に衝突リストにあるなら何もしない
	if (me->IsInHitBulletList(playerBullet)) return;

	// 衝突リストに追加
	me->AddHitBullet(playerBullet);

	// 状態をダメージに変更
	me->nextAnimationState = EnemyFactory::EnemyFactoryAnimationState::kDamage;

	// ダメージ表示
	DamageDisplay::Get()->Activate(playerBullet->GetAttackPower(), me->Getter_Trans()->GetWorldPos(),
		1.0f, { 255,255,0 });

	// ダメージ処理
	me->hp = me->hp - playerBullet->GetAttackPower();
	if (me->hp <= 0.0f)
	{
		me->SwitchCollisionActivation(false);
		me->nextAnimationState = EnemyFactory::EnemyFactoryAnimationState::kDead;
		me->isDead = true;
		me->buildingsManager->NotifyEnemyFactoryDead(me);
	}
}


