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

	struct uiData
	{
		std::unique_ptr<Sprite> sprite;
		Vector2 position;
	};
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

private:

	UIMode mode = UIMode::None;

public:

	// UIモード設定
	void SetUIMode(UIMode mode_);

	// スーパードロー
	void SuperDraw(Matrix4* vpMat_);

	// デバッグ描画
	void DebugDraw();

	void LoadData();
	void SaveData();

private:

	std::vector<size_t> drawOrder;
	std::map<uiType, uiData> uiElements;

	void DrawTitleUI(Matrix4* vpMat_);
	void DrawStageSelectUI(Matrix4* vpMat_);
	void DrawInGameUI(Matrix4* vpMat_);

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

