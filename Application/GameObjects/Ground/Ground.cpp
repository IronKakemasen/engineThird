#include "Ground.h"
#include "../../GameObjects/InGameController/InGameController.h"
#include "imgui.h"

//コリジョンバックテーブルを設定
void Ground::SetCollisionBackTable()
{
	path = "./resource/application/json/ground/groundData.json";

}



void Ground::LoadData()
{
	if (status == Status::kInActive) return;

	// 現在選択されているステージでのアクティブ数を取得
	Json::LoadParam(path, "/stage" + std::to_string(tempStageNumber) + "/size", trans.scale);
}

void Ground::SaveData()
{
	if (status == Status::kInActive) return;

	Json::SaveParam(path, "/stage" + std::to_string(tempStageNumber) + "/size", trans.scale);
	Json::Save(path);
}

void Ground::DebugDraw()
{
#ifdef USE_IMGUI

	if (status == Status::kInActive) return;

	std::string key = "##" + std::to_string(ID);

	ImGui::DragFloat3((key + "scale.x").c_str(), &trans.scale.x, 0.1f);
	if (ImGui::Button((std::to_string(ID) + ":Save").c_str()))
	{
		SaveData();
	}
	ImGui::SameLine();
	if (ImGui::Button((std::to_string(ID) + ":Load").c_str()))
	{
		LoadData();
	}

#endif // USE_IMGUI
}

void Ground::ReplaceOnMap(const int32_t stage)
{
	tempStageNumber = stage;

	// アクティブ化
	status = Status::kActive;
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(false);
	// データ読み込み
	LoadData();
}

void Ground::Update()
{
	//モデルの更新処理（中身を書いていれば）
	groundPlane->Update();

}

void Ground::Init()
{
	//モデルの初期化
	groundPlane->Init(&trans);
	groundPlane->model->GetAppearance(0)->color = { 255,255,255,255 };

	//identityTableにセットされている通りに、identityを定める
	//タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kNone);
	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	//衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

}

void Ground::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	groundPlane->Reset();

	// 現在選択されているステージ
	ReplaceOnMap(inGameController->curStage);
}

void Ground::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	groundPlane->Draw(vpMat_);
}

void Ground::DrawHpBar(Matrix4* vpMat_)
{}


Ground::Ground()
{
	//モデルのインスタンス化
	groundPlane.reset(new GroundPlane);
}
