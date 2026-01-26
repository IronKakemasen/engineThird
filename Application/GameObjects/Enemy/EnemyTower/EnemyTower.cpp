#include "EnemyTower.h"
#include "../Json/Json.h"
#include "../../../Config/InGameConfig.h"
#include "../../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "imgui.h"

EnemyTower::EnemyTower()
{
	//モデルのインスタンス化
	model.reset(new EnemyTowerModel);

	//必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };

	// Jsonパスの設定
	path = "./resource/application/json/enemy/enemyTowerData.json";
}

void EnemyTower::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 現在選択されているステージでのアクティブ数を取得
	Json::LoadParam(path, "/stage" + std::to_string(StageCount) + "/ActiveCount", stageActiveCounts);

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

	// config反映
	hp = inGameConfig->enemyTowerMaxHP;
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

	std::string key = "/stage" + std::to_string(StageCount) + "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
}
void EnemyTower::SaveData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(StageCount) + "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

void EnemyTower::Update()
{
	model->Update();
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

	me->hp = me->hp - playerBullet->GetAttackPower();

	if (me->hp < 0.0f)
	{
		me->SetStatus(Status::kInActive);
	}
}



