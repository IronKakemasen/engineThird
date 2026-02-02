#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/EnemyFactoryModel/EnemyFactoryModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectBuilding.h"
#include "../../BuildingsManager/BuildingsManager.h"

struct Enemy;
struct PlayerBullet;

struct EnemyFactory :public GameObject, public GameObjectBuilding
{
#pragma region 独自部位

private:

	// 参照ポインタ
	std::vector<Enemy*> enemies{};

	Counter spawnCounter;

	// 衝突弾リスト更新
	void UpdateHitBullets();
	// そのターンで衝突した弾のリスト（多重衝突防止用）
	std::vector<PlayerBullet*> hitBullets{};

	bool isDead = false;
public:
	Counter rebornCounter;
	bool IsDead() const { return isDead; }
	 
	// 衝突した弾をリストに追加
	void AddHitBullet(PlayerBullet* bullet);
	// その弾が既に衝突リストにあるか
	bool IsInHitBulletList(PlayerBullet* bullet);

	// エネミー生産
	void SpawnEnemy();

#pragma	endregion

#pragma region 共通部位

public:
	// データの読み込み・保存
	void LoadData() override;
	void SaveData() override;

	// マップに配置
	void ReplaceOnMap(const int32_t stage) override;

	// デバッグ描画
	void DebugDraw() override;

	// BuildingsManagerセット
	void SetBuildingsManager(BuildingsManager* manager_) override
	{
		buildingsManager = manager_;
		buildingsManager->SetEnemyFactory(this);
	}


	int32_t tempStageNumber = -1;

#pragma endregion

#pragma region 基盤部位

private:

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayerBullet
	{
		EnemyFactory* me = nullptr;
		void operator()();
		void Init(EnemyFactory* object) { me = object; }
	};
	// プレイヤー弾と衝突したときのコリジョンバック
	CollisionBackToPlayerBullet collisionBackToPlayerBullet;

public:
	//使用するモデル
	std::unique_ptr<EnemyFactoryModel> model;

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

	EnemyFactory();

#pragma endregion
};

