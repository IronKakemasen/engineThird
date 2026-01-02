#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"

struct BlackBlock;
struct GreenBlock;
struct NormalBlock;

struct BlockManager :public  GameObject
{
private:

	struct WaveData
	{
		Vector2 startSize;
		Vector4 color;
		std::vector<std::vector<int>> map;
		void Init(Vector2 startSize_, Vector4 color_);
	};
	int const height = 3;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	static inline int const kNumNormalBlock = 300;
	static inline int const kNumBlackBlock = 30;
	static inline int const kNumGreenBlock = 30;
	static inline Vector3 const kStartPos = { 100,100,100 };
	static inline float curLastPosZ = kStartPos.z;
	static inline WaveData waveData[2];

	std::vector<GameObject* >normalBlocks;
	std::vector<GameObject*> blackBlocks;
	std::vector<GameObject*> greenBlocks;

	void SetNormalBlock(NormalBlock* nomal_);
	void SetBlackBlock(BlackBlock* black_);
	void SetGreenBlock(GreenBlock* green_);

	BlockManager();

private:
	void SetGround();
	void TurnBlocksIsActiveOff();
};

