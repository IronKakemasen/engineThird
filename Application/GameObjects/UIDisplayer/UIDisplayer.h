#pragma once
#include "GameObjectBehavior.h"
#include "Sprite.h"


struct UIDisplayer :public GameObject
{
	enum class UIMode
	{
		TiTle,
		StageSelect,
		InGame,
		None,
	};

private:

	UIMode mode = UIMode::None;

public:

	void SetUIMode(UIMode mode_) { mode = mode_; };

	void SuperDraw(Matrix4* vpMat_);
private:
	//使用するテクスチャ
	std::unique_ptr<Sprite> buttonBack900x250;
	std::unique_ptr<Sprite> buttonDecision900x250;
	std::unique_ptr<Sprite> buttonMove900x250;
	std::unique_ptr<Sprite> buttonOption900x250;
	std::unique_ptr<Sprite> buttonPause900x250;
	std::unique_ptr<Sprite> buttonShot900x250;
	std::unique_ptr<Sprite> buttonZoom900x250;

	std::unique_ptr<Sprite> numbers100x100;

	std::unique_ptr<Sprite> stage1Name1000x100;
	std::unique_ptr<Sprite> stage2Name1000x100;
	std::unique_ptr<Sprite> stage3Name1000x100;
	std::unique_ptr<Sprite> stage4Name1000x100;
	std::unique_ptr<Sprite> stage5Name1000x100;

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

