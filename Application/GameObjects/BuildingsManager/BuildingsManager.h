#pragma once
#include "GameObjectBehavior.h"
#include "../../GameObjects/ObjectParent/GameObjectBuilding.h"
#include "../../Models/Shikoutei/ShikouteiModel.h"
#include <vector>

struct EnemyFactory;
struct EnemyTower;
struct PlayerTower;

struct BuildingsManager :public GameObject, public GameObjectBuilding
{
private:

	void LoadData() override;
	void SaveData() override;
	void DebugDraw() override;

	std::vector<EnemyFactory*> enemyFactories{};
	std::vector<EnemyTower*> enemyTowers{};
	std::vector<PlayerTower*> playerTowers{};

public:

	void SetEnemyFactory(EnemyFactory* factory);
	void SetEnemyTower(EnemyTower* tower);
	void SetPlayerTower(PlayerTower* tower);

	// エネミーファクトリが死んだときこの関数を呼び出す
	// 呼び出されてから一定時間後にエネミーファクトリを復活させる
	void NotifyEnemyFactoryDead(EnemyFactory* factory);


	// マップに配置
	void ReplaceOnMap(const int32_t stage) override;
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

	BuildingsManager();
};

