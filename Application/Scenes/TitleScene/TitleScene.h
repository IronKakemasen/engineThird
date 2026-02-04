#pragma once
#include "SceneBehavior.h"
#include "../../GameObjects/ForTitleScene/ForTitleScene.h"
#include "../../Cameras/TitleCamera/TitleCamera.h"

class TitleScene final : public Scene
{
	std::unique_ptr<ForTitleScene> forTitleScene;
	PointLight* pLights[2];
	TitleCamera titleCamera;
	bool pushed = false;

public:
	static inline int mode = 0;
	static inline Counter c;

	TitleScene();

	//↓呼び出す必要なし。↓
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() override;
	//リセット処理。
	virtual void Reset() override;
	//デバッグ処理。各シーンのImGui表示はここで。
	virtual void Debug() override;
	//インスタンス化処理を書く場所
	virtual void Instantiate() override;
	//初期化処理を書く場所
	virtual void Init() override;

};

