#pragma once
#include "GameObjectBehavior.h"
#include "Sprite.h"
#include <array>
#include <map>

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
		Back200x60,
		Decision200x60,
		Move200x60,
		Option200x60,
		Pause200x60,
		Shot200x60,
		Zoom200x60,
		Reticle200x60,
		Numbers1000x100,
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
		case UIDisplayer::uiType::Back200x60:
			return "Back";
			break;
		case UIDisplayer::uiType::Decision200x60:
			return "Decision";
			break;
		case UIDisplayer::uiType::Move200x60:
			return "Move";
			break;
		case UIDisplayer::uiType::Option200x60:
			return "Option";
			break;
		case UIDisplayer::uiType::Pause200x60:
			return "Pause";
			break;
		case UIDisplayer::uiType::Shot200x60:
			return "Shot";
			break;
		case UIDisplayer::uiType::Zoom200x60:
			return "Zoom";
			break;
		case UIDisplayer::uiType::Numbers1000x100:
			return "Numbers";
			break;
		case UIDisplayer::uiType::Stage1Name1000x100:
			return "Stage1Name";
			break;
		case UIDisplayer::uiType::Stage2Name1000x100:
			return "Stage2Name";
			break;
		case UIDisplayer::uiType::Stage3Name1000x100:
			return "Stage3Name";
			break;
		case UIDisplayer::uiType::Stage4Name1000x100:
			return "Stage4Name";
			break;
		case UIDisplayer::uiType::Stage5Name1000x100:
			return "Stage5Name";
			break;
		case UIDisplayer::uiType::MAX:
			break;
		default:
			break;
		}
		return "";
	}

	struct uiData
	{
		std::unique_ptr<Sprite> sprite;
		Vector2 position;
		Vector2 scale = Vector2(1.1f, 1.1f);
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

	std::vector<uiType> drawOrder;
	std::map<uiType, uiData> uiElements;

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

