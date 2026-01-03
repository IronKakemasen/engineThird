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
	std::vector<NormalBlock* >normalBlocks;
	std::vector<BlackBlock*> blackBlocks;
	std::vector<GreenBlock*> greenBlocks;
	std::vector<NormalBlock* > additions;
	int const numAdd = 350;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;

	static constexpr float kBlockSize = 1.0f;
	static inline int const kNumNormalBlock = 450;
	static inline int const kNumBlackBlock = 30;
	static inline int const kNumGreenBlock = 30;
	static inline Vector3 const kStartPos = { 100,100,100 };
	static inline float curLastPosZ = kStartPos.z;
	static inline WaveData waveData[2];
	static inline  int mapLast;
	

	void SetNormalBlock(NormalBlock* nomal_);
	void SetBlackBlock(BlackBlock* black_);
	void SetGreenBlock(GreenBlock* green_);

	BlockManager();

private:
	void SetGround();
	void TurnBlocksIsActiveOff();
	void SetAdditions();
	void AddBlockToLast();
};

