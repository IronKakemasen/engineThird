#include "EnemyFactory.h"
#include "../Json/Json.h"
#include "imgui.h"
#include "../../../Config/GameConstants.h"

EnemyFactory::EnemyFactory()
{
	//モデルのインスタンス化
	model.reset(new EnemyFactoryModel);

	//必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };

	// Jsonパスの設定
	path = "./resource/application/json/enemy/enemyFactoryData.json";
}

void EnemyFactory::Reset()
{
	// モデルのリセット（中身が書いてあれば）
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
}

void EnemyFactory::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kEnemyFactory);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackToPlayerBulletの初期化
	collisionBackToPlayerBullet.Init(this);
	
	// 初期化
	Reset();
}

void EnemyFactory::SetCollisionBackTable()
{
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
}

// データ保存・読み込み
void EnemyFactory::LoadData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(StageCount) + "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
}
void EnemyFactory::SaveData()
{
	if (status == Status::kInActive) return;

	std::string key = "/stage" + std::to_string(StageCount) + "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::Save(path);
}

void EnemyFactory::Update()
{
	model->Update();
}

void EnemyFactory::Draw(Matrix4 * vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
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
	me->SetStatus(Status::kInActive);
}


