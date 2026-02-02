#include "PlayerTower.h"
#include "../Json/Json.h"
#include "imgui.h"
#include "../../../Config/InGameConfig.h"
#include "../../../GameObjects/Enemy/Enemy.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../../GameObjects/InGameController/InGameController.h"

//
PlayerTower::PlayerTower()
{
	// モデルのインスタンス化
	model.reset(new PlayerTowerModel);
	circleModel.reset(new CircleModel);
	circleModel->defaultScale = { 9.0f,1,9.0f };
	auto* c = circleModel->model->GetAppearance(0);
	//c->shaderSetIndex =
	//	M::GetInstance()->GetShaderSetIndexFromFileName("ModelNoLight.VS", "ModelNoLight.PS");

	c->color = { 150,150,255,255 };

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
	model->Update();
	circleModel->Update();

#ifdef _DEBUG
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerTowerCollisonSize);
#endif // _DEBUG
}

// 描画処理
void PlayerTower::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
	circleModel->Draw(vpMat_);

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

	me->hp = me->hp - enemy->GetAttackPower();

	if (me->hp <= 0.0f)
	{
		me->SetStatus(Status::kInActive);
	}
}
