#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/PlayerModel/PlayerModel.h"
#include "../../GameObjects/ObjectParent/GameObjectEntity.h"
#include "../../Config/GameConstants.h"
#include <array>
#include <queue>

struct PlayerAlly;
struct PlayerBullet;

struct Player :public GameObject, public GameObjectEntity
{
#pragma region 独自部位

private:
	//////  移動処理  //////
	void Move();			// 移動
	bool isMoving = false;	// 移動中フラグ

	//////  攻撃処理  //////
	void Attack();		// 攻撃
	std::vector<PlayerBullet*> bullets{}; // 参照ポインタ
	Counter attackIntervalCounter;		// 攻撃間隔カウンター

	///// 座標履歴管理処理  //////
	void SavePos();			// 座標履歴の保存
	Vector3 GetPosHistory(int32_t n);// nフレーム前の座標を取得
	// 自身の座標履歴[最大味方数 * 味方追従遅延フレーム数]
	std::array<Vector3, GameConstants::kMaxAllies* GameConstants::kAllyFollowDelayFramesMax> posHistory = {};
	size_t headIndex = 0;	// リングバッファの先頭インデックス

	////// 分離数設定処理  //////
	void UpdateAllySeparate();

	////// 視線変更処理  //////
	void UpdateLookDir();
	

	////// 味方自動補充処理  //////
	void AutoSpawnAlly();
	Counter autoSpawnAllyCounter;

	////// 味方管理処理  //////
	void UpdateAllyData(); // 味方データ更新処理
	std::vector<PlayerAlly*> allies{};	// 参照ポインタ
	// 列に並んでいる味方の数
	int32_t formedAllyCount = 0;
	// 列に並んでいない味方の数
	int32_t unformedAllyCount = 0;


	// 前からn番目の味方が存在するかのフラグ
	// [n]が死んだ瞬間にdeadIndexList.push(n);
	std::array<bool, GameConstants::kMaxAllies> exist = {};

	// 味方の遅延フレームオフセット
	// 例：	[n]が死亡した場合
	//		deadIndexList.empty() == falseなら
	//		プレイヤーが停止している時、delayFrameOffsetsが1ずつ増える
	//      delayFrameOffsetsがkAllyFollowDelayFramesと同値になったら１人分詰め切ったと判断し
	//		delayFrameOffsets を 0 にリセットする
	//		deadIndexList.pop() して次の味方の詰め待ちに移行する
	//	    
	// 要約:自分より前の味方が死んだ時後ろの味方すべてが詰める。そのオフセット管理用
	int32_t delayFrameOffsets = 0;
	// 死亡して詰め待ちのリスト(先入れ先出し)
	//std::deque<int32_t> deadIndexList = {};


public:

	/// <summary>
	/// 味方の目標座標を取得
	/// </summary>
	/// <param name="allyIndex"> 列の前から何番目か(並んでない時は-1) </param>
	Vector3 GetAllyTargetPos(int32_t allyIndex);

	/// <summary>
	/// 最後尾に並ぶことを試みる
	/// </summary>
	/// <returns> 失敗したら-1 </returns>
	int32_t TryReserveFormationIndex();

	/// <summary>
	/// そのフレームで分離する味方の数を取得
	/// </summary>
	/// <returns> 分離がないなら-1 </returns>
	int32_t GetSeparateAllyCount() const;

	// 動いているかどうか
	bool IsMoving() const { return isMoving; }


	float GetSpeed() const;

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

	static inline Vector3 deltaPos;
	// 使用するモデル
	std::unique_ptr<PlayerModel> model;

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
	inline bool WatchIsMove() { return isMoving; }


	Player();

private:

#pragma endregion
};

