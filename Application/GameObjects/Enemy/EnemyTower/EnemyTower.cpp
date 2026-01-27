#include "EnemyTower.h"
#include "../Json/Json.h"
#include "../../../Config/InGameConfig.h"
#include "../../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../../GameObjects/InGameController/InGameController.h"
#include "imgui.h"

EnemyTower::EnemyTower()
{
	//モデルのインスタンス化
	model.reset(new EnemyTowerModel);

	// Jsonパスの設定
	path = "./resource/application/json/enemy/enemyTowerData.json";
}

void EnemyTower::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 現在選択されているステージでのアクティブ数を取得
	Json::LoadParam(path, "/stage" + std::to_string(inGameController->curStage) + "/ActiveCount", stageActiveCounts);

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

void EnemyTower::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kEnemyTower);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);

	// collisionBackToPlayerBulletの初期化
	collisionBackToPlayerBullet.Init(this);
}

void EnemyTower::SetCollisionBackTable()
{
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
}

// データ保存・読み込み
void EnemyTower::LoadData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);

	/// config反映
	// HP設定
	hp = inGameConfig->enemyTowerMaxHP;
}
void EnemyTower::SaveData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(inGameController->curStage) + "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

void EnemyTower::Update()
{
	model->Update();

	// 衝突弾リスト更新
	UpdateHitBullets();
}

void EnemyTower::AddHitBullet(PlayerBullet* bullet)
{
	hitBullets.push_back(bullet);
}

bool EnemyTower::IsInHitBulletList(PlayerBullet* bullet)
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

void EnemyTower::UpdateHitBullets()
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

void EnemyTower::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
}

void EnemyTower::DebugDraw()
{
#ifdef USE_IMGUI

	if (status == Status::kInActive) return;

	std::string key = std::to_string(ID) + "##";

	ImGui::PushItemWidth(100.0f);
	ImGui::DragFloat((key + "position.x").c_str(), &trans.pos.x, 0.1f);
	ImGui::SameLine();
	ImGui::DragFloat((key + "position.z").c_str(), &trans.pos.z, 0.1f);
	if (ImGui::Button(("Save##" + std::to_string(ID)).c_str()))
	{
		SaveData();
	}
	ImGui::SameLine();
	if (ImGui::Button(("Load##" + std::to_string(ID)).c_str()))
	{
		LoadData();
	}
	ImGui::SameLine();
	if (ImGui::Button(("Reset##" + std::to_string(ID)).c_str()))
	{
		Reset();
	}

#endif // USE_IMGUI
}

// プレイヤー弾との衝突
void EnemyTower::CollisionBackToPlayerBullet::operator()()
{
	auto* playerBullet = reinterpret_cast<PlayerBullet*>(me->Getter_ColObj());
	
	// 既に衝突リストにあるなら何もしない
	if (me->IsInHitBulletList(playerBullet)) return;

	// 衝突リストに追加
	me->AddHitBullet(playerBullet);

	me->hp = me->hp - playerBullet->GetAttackPower();
	if (me->hp <= 0.0f)
	{
		me->SetStatus(Status::kInActive);
	}
}



