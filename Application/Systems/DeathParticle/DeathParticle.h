#pragma once
#include "../../M/lowerLayer/MobilePrimitive/MobileTriangle/MTriangle/MTriangle.h"
#include "../../GameObject/GameObjectBehavior.h"

class GameObjectManager;

struct DeathParticleObject :public GameObject
{
	static inline int const kMax = 1024;

	struct Trianglele
	{
		MTriangle mTriangle;
		bool isActive = false;
		Vector3 pulseDir;
		Vector3 velocity;
	};

public:
	std::vector<std::unique_ptr<Trianglele>> triangles;

	DeathParticleObject();

	//↓ゲームオブジェクトマネージャーに登録すれば呼び出す必要なし↓
	// 更新処理。
	// GameObject::StateがinActiveの場合は呼び出されない
	virtual void Update()override;
	//初期化処理
	virtual void Init() override;
	//リセット処理（ゲームループ等シーンのリセットに呼び出す）
	virtual void Reset() override {};
	//描画処理.StateがinActiveの場合は呼び出されない
	virtual void Draw(Matrix4* vpMat_)override;
	//コリジョンをセットする関数
	virtual void SetCollisionBackTable() {};

};


class DeathParticle
{
	DeathParticleObject deathParticleObject;

public:

	static DeathParticle* Get();
	void Activate(Vector3 world_, int num_, float power_ , float scale_, Vector3 color_);
	void Init(GameObjectManager* gameObjectManager_);
	void Update();
	void Draw(Matrix4* vpMat_);

};

