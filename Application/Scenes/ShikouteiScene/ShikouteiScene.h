#pragma once
#include "SceneBehavior.h"
#include"../../GameObjects/Shikoutei/Shikoutei.h"
#include"../../GameObjects/ExampleTyan/ExampleTyan.h"
#include "../../GameObjects/Enemy/EnemyFactory/EnemyFactory.h"
#include "../../Cameras/MainCamera/MainCamera.h"

#include "../../GameObjects/Player/Player.h"

class ShikouteiScene final : public Scene
{
	//そのシーンのカメラのトランスフォームをいただく
	MainCamera mainCamera;

	//使用するゲームオブジェクト
	std::unique_ptr<Shikoutei> shikoutei;
	std::unique_ptr<ExampleTyan> exampleTyan;
	std::unique_ptr<Player> player;
	std::unique_ptr<EnemyFactory> enemyFactory;


	MQuad quad;
	Sprite sprite;
	Sprite atlasNumber;
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

