#pragma once
#include "SceneBehavior.h"
#include"../../GameObjects/Shikoutei/Shikoutei.h"
#include "../../Cameras/MainCamera/MainCamera.h"

class ShikouteiScene final : public Scene
{
	//そのシーンのカメラのトランスフォームをいただく
	MainCamera mainCamera;


	//使用するゲームオブジェクト
	std::unique_ptr<Shikoutei> shikoutei;

public:
	ShikouteiScene();

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

