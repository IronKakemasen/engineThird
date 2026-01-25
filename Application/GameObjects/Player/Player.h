#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/PlayerModel/PlayerModel.h"
#include "../../GameObjects/ObjectParent/GameObjectEntity.h"
#include "../../Config/GameConstants.h"
#include <array>

struct PlayerAlly;
struct PlayerBullet;

struct Player :public GameObject, public GameObjectEntity
{
#pragma region 独自部位

private:
	//////  移動処理  //////
	void Move();			// 移動
	bool isMoving = false;	// 移動中フラグ
	//int32_t stopMoveFrame = 0;// 移動停止してからのフレーム数
	float speed = 0.1f;		// 移動速度

	//////  攻撃処理  //////
	void Attack();		// 攻撃
	std::vector<PlayerBullet*> bullets{}; // 参照ポインタ
	float attackGauge = 3.0f;		// 攻撃ゲージ(0.0f ~ 3.0f)攻撃一回で1.0f減少 減った後残3.0f~2.0fの攻撃はステージ１　2.0f~1.0f


	///// 座標履歴管理処理  //////
	void SavePos();			// 座標履歴の保存
	// 自身の座標履歴[最大味方数 * 味方追従遅延フレーム数]
	std::array<Vector3, GameConstants::kMaxAllies* GameConstants::kAllyFollowDelayFrames> posHistory = {};
	size_t headIndex = 0;	// リングバッファの先頭インデックス


	////// 視線変更処理  //////
	void UpdateLookDir();
	

	////// 味方管理処理  //////
	void UpdateAllyData(); // 味方データ更新処理
	std::vector<PlayerAlly*> allies{};	// 参照ポインタ
	// 配置インデックスが空いているかのフラグ[最大味方数]
	std::array<bool, GameConstants::kMaxAllies> allyExistenceFlags = {};
	// そのインデックスの味方が目指すべきインデックス[最大味方数]
	std::array<int32_t, GameConstants::kMaxAllies> allyTargetIndices = {};
	// 列に並んでいる味方の数
	int32_t formedAllyCount = 0;
	// 列に並んでいない味方の数
	int32_t unformedAllyCount = 0;


public:

	/// <summary>
	/// 味方の目標座標を取得
	/// </summary>
	/// <param name="allyIndex"> 列の前から何番目の座標か </param>
	/// <returns></returns>
	Vector3 GetAllyTargetPos(int32_t allyIndex);

	/// <summary>
	/// 自身が目指すべき次の空いている味方インデックスを取得
	/// </summary>
	/// <param name="currentIndex"> 現在のインデックス(-1はまだ列に加わっていない) </param>
	/// <returns></returns>
	int32_t GetAllyTargetIndex(int32_t currentIndex);

	/// <summary>
	/// 列ぬ加入している味方の生存フラグをセット
	/// </summary>
	/// <param name="index"> インデックス </param>
	/// <param name="flag"> フラグ </param>
	/// <returns> 成功したらtrue </returns>
	bool TryReserveFormationIndex(int32_t preferredIndex);

	/// <summary>
	/// currentIndexの前に味方が存在するか
	/// </summary>
	/// <param name="currentIndex"> 現在のインデックス </param>
	/// <returns> 存在するならtrue </returns>
	bool IsExistFrontAlly(int32_t currentIndex);

	// 動いているかどうか
	bool IsMoving() { return isMoving; }

	float GetSpeed() { return speed; }


	// 味方の参照ポインタを追加
	void SetAllies(PlayerAlly* allyPoint) { allies.push_back(allyPoint); }
	// 弾の参照ポインタを追加
	void SetBullets(PlayerBullet* bullet) { bullets.push_back(bullet); }

	// 味方を生み出す
	void SpawnAlly(Vector3 pos);

#pragma	endregion

#pragma region 共通部位

public:
	// データの読み込み・保存
	void LoadData() override;
	void SaveData() override;

	// デバッグ描画
	void DebugDraw() override;

#pragma endregion

#pragma region 基盤部位

private:
	// 使用するモデル
	std::unique_ptr<PlayerModel> model;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToEnemy
	{
		Player* me = nullptr;
		void operator()();
		void Init(Player* object) { me = object; }
	};
	// Enemyと衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;


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


	Player();

#pragma endregion
};

