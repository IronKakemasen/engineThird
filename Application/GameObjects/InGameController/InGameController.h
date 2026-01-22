#pragma once
#include "GameObjectBehavior.h"
#include "Actor.h"
#include "../../Models/PlayerModel/PlayerModel.h"


struct Player;

struct InGameController:public GameObject
{
	enum Mode
	{
		kEnter,
		kPlayable,
		kUnPlayable,
		kResult,
		kGameOver,

		kCount
	};

private:

	struct ModeData
	{
		float time;
		void Set(float time_);
	};

	ModeData modeData[Mode::kCount];

	//使用するモデル
	std::unique_ptr<PlayerModel> model;
	//プレイヤー
	Player* player = nullptr;

	std::unordered_map<Mode, std::unique_ptr<actor::Actor>> actors;
	Mode mode = kPlayable;
	float count = 0.0f;;

	void SetModeData();
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

	std::string WathchInString();
	float* GetCnt();

	InGameController();

};

