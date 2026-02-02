#pragma once
#include "GameObjectBehavior.h"
#include "Sprite.h"
#include <array>
#include <map>

struct InGameController;

struct UIDisplayer :public GameObject
{
	enum class UIMode
	{
		TiTle,
		StageSelect,
		InGame,
		Pause,
		None,
	};
	std::string toString(UIMode uiMode)
	{
		switch (uiMode)
		{
		case UIDisplayer::UIMode::TiTle:
			return "TiTle";
			break;
		case UIDisplayer::UIMode::StageSelect:
			return "StageSelect";
			break;
		case UIDisplayer::UIMode::InGame:
			return "InGame";
			break;
		case UIDisplayer::UIMode::Pause:
			return "Pause";
			break;
		case UIDisplayer::UIMode::None:
			return "None";
			break;
		default:
			break;
		}
		return "";
	}

	enum class uiType
	{
		// 汎用
		Numbers1000x100,	// 数字
		Cursor50x50,		// カーソル

		// 操作説明UI
		Back200x60,		// モドル
		Decision200x60,	// ケッテイ
		Move200x60,		// イドウ
		Option200x60,	// セッテイ
		Pause200x60,	// ポーズ
		Reticle200x60,	// ネラウ
		Set200x60,		// ハイチ
		Shot200x60,		// ショット
		Zoom200x60,		// ズーム

		// ポーズUI
		PauseTitle500x100, 		// ポーズタイトル
		PauseButton01_350x50,	// プレイ
		PauseButton02_350x50,	// リトライ
		PauseButton03_350x50,	// オプション
		PauseButton04_350x50,	// セレクト
		PauseScreen_1280x720,	// ポーズ背景

		// インゲームUI
		GameOver1000x200,		// ゲームオーバー
		StageClear1000x200,		// ゲームクリア

		// ステージセレクト
		Stage1Name1000x100,
		Stage2Name1000x100,
		Stage3Name1000x100,
		Stage4Name1000x100,
		Stage5Name1000x100,

		MAX,
	};
	std::string toString(uiType ui)
	{
		switch (ui)
		{
		case uiType::Numbers1000x100:     return "Numbers";
		case uiType::Cursor50x50:         return "Cursor";

		case uiType::Back200x60:          return "Back";
		case uiType::Decision200x60:      return "Decision";
		case uiType::Move200x60:          return "Move";
		case uiType::Option200x60:        return "Option";
		case uiType::Pause200x60:         return "Pause";
		case uiType::Reticle200x60:       return "Reticle";
		case uiType::Set200x60:           return "Set";
		case uiType::Shot200x60:          return "Shot";
		case uiType::Zoom200x60:          return "Zoom";

		case uiType::PauseTitle500x100:   return "PauseTitle";
		case uiType::PauseButton01_350x50:return "PauseButton01";
		case uiType::PauseButton02_350x50:return "PauseButton02";
		case uiType::PauseButton03_350x50:return "PauseButton03";
		case uiType::PauseButton04_350x50:return "PauseButton04";
		case uiType::PauseScreen_1280x720:return "PauseScreen";

		case uiType::GameOver1000x200:    return "GameOver";
		case uiType::StageClear1000x200:  return "StageClear";

		case uiType::Stage1Name1000x100:  return "Stage1Name";
		case uiType::Stage2Name1000x100:  return "Stage2Name";
		case uiType::Stage3Name1000x100:  return "Stage3Name";
		case uiType::Stage4Name1000x100:  return "Stage4Name";
		case uiType::Stage5Name1000x100:  return "Stage5Name";

		case uiType::MAX:                 return "MAX";
		default:                          return "";
		}
	}


	struct uiData
	{
		std::unique_ptr<Sprite> sprite;
		Vector2 initPosition = Vector2(100.0f, 100.0f);
		Vector2 curPos = Vector2(100.0f, 100.0f);
		Vector2 initScale = Vector2(1.0f, 1.0f);
		Vector2 curScale = Vector2(1.0f, 1.0f);
	};

private:

	UIMode mode = UIMode::None;

	std::string path = "./resource/application/json/config/ui.json";

public:

	// UIモード設定
	void SetUIMode(UIMode mode_);

	// スーパードロー
	void SuperDraw(Matrix4* ortho_);

	// デバッグ描画
	void DebugDraw();

	void LoadData();
	void SaveData();

private:
	InGameController* inGameController = nullptr;

	std::vector<uiType> drawOrder;
	std::map<uiType, uiData> uiElements;

	float pauseScreenOffset = 0.0f;

public:
	//↓ゲームオブジェクトマネージャーに登録すれば呼び出す必要なし↓
	// 更新処理。
	// GameObject::StateがinActiveの場合は呼び出されない
	virtual void Update()override;
	//初期化処理
	virtual void Init() override;
	//リセット処理（ゲームループ等シーンのリセットに呼び出す）
	virtual void Reset() override;
	//描画処理.StateがinActiveの場合は呼び出されない
	virtual void Draw(Matrix4* vpMat_)override;
	//コリジョンをセットする関数
	virtual void SetCollisionBackTable()override;

	UIDisplayer();
};

