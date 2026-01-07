#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "../Model/PlayerModel.h"

struct BlueMark;
struct RedMark;


struct Player : public GameObject
{
	struct ToBlock
	{
		Player* p;
		bool operator()();
		void Init(Player* p_);
	};

	bool IsDeath();
	void ClipPosition();
	void Move();
	void SetStart();
	void PutMark();
	void ActivateMark();
	void Mark();
	void ActivateAllMidori();

	float const moveSpeed = 2.75f;
	Counter angleCnt;
	float nextAngleY = 0.0f;
	float preAngleY = 0.0f;
	float const playerSize = 0.2f;
public:

	ToBlock toBlock;
	std::vector<RedMark*> redMarks;
	std::unique_ptr<PlayerModel> model;
	BlueMark* blueMark = nullptr;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	Player();
};

Vector3 GetCollisionPushback(const Rect& dynamicRect, const Rect& staticRect,
	Vector3 c1_, Vector3 c2_);
