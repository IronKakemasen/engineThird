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
		Back900x250,
		Decision900x250,
		Move900x250,
		Option900x250,
		Pause900x250,
		Shot900x250,
		Zoom900x250,
		Numbers100x100,
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
		case UIDisplayer::uiType::Back900x250:
			return "Back";
			break;
		case UIDisplayer::uiType::Decision900x250:
			return "Decision";
			break;
		case UIDisplayer::uiType::Move900x250:
			return "Move";
			break;
		case UIDisplayer::uiType::Option900x250:
			return "Option";
			break;
		case UIDisplayer::uiType::Pause900x250:
			return "Pause";
			break;
		case UIDisplayer::uiType::Shot900x250:
			return "Shot";
			break;
		case UIDisplayer::uiType::Zoom900x250:
			return "Zoom";
			break;
		case UIDisplayer::uiType::Numbers100x100:
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

