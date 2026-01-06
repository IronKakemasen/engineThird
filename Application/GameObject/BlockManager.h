#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"

struct BlackBlock;
struct GreenBlock;
struct NormalBlock;


struct BlockPatternData
{
	static int const kNumPattern = 8;
	int pattern0[kNumPattern][2][4] =
	{	
		{
			{1,0,1,2},
			{1,1,1,1}
		},
		{
			{1,1,0,1},
			{1,0,1,1}
		},
		{
			{1,1,0,1},
			{0,1,1,1}
		},
		{
			{0,0,0,0},
			{1,2,2,2}
		},
		{
			{0,1,1,0},
			{1,0,0,1}
		},
		{
			{1,1,1,1},
			{2,0,2,1}
		},
		{
			{1,0,1,1},
			{1,1,1,2}
		},
		{
			{1,1,1,1},
			{0,0,1,1}
		},
	};
	int pattern1[kNumPattern][3][4] =
	{
		{
			{1,1,1,2},
			{1,1,1,1},
			{1,0,1,1}
		},
		{
			{1,1,1,1},
			{1,0,1,2},
			{1,1,1,2}
		},
		{
			{1,0,1,2},
			{1,1,0,1},
			{1,0,1,1}
		},
		{
			{1,1,1,1},
			{1,2,1,1},
			{1,1,1,0}
		},
		{
			{1,0,1,2},
			{1,1,0,1},
			{1,0,1,1}
		},
		{
			{1,1,0,1},
			{1,1,0,1},
			{0,1,1,1}
		},
		{
			{1,0,1,1},
			{1,1,1,1},
			{2,2,1,1}
		},
		{
			{1,1,0,2},
			{1,0,1,1},
			{0,1,1,1}
		},
	};

	int pattern2[kNumPattern][4][5]
	{
		{
			{1,1,1,2,1},
			{1,2,2,0,1},
			{1,1,1,1,1},
			{0,1,2,2,0}
		},
		{
			{1,1,1,1,1},
			{1,2,1,1,1},
			{2,2,0,1,2},
			{1,1,1,1,0}
		},
		{
			{1,0,1,0,1},
			{2,1,1,1,1},
			{1,1,0,2,1},
			{1,0,1,2,1}
		},
		{
			{0,1,1,1,1},
			{1,0,1,1,1},
			{1,1,1,1,1},
			{1,1,0,1,0}
		},
		{
			{1,1,1,1,1},
			{2,2,2,1,1},
			{2,2,2,1,1},
			{2,0,2,1,0}
		},
		{
			{1,1,1,2,2},
			{1,2,1,1,1},
			{1,0,1,1,1},
			{1,0,1,0,1}
		},
		{
			{1,1,1,1,1},
			{1,2,1,1,1},
			{2,2,0,1,2},
			{1,1,1,1,0}
		},
		{
			{1,1,1,2,1},
			{1,2,2,0,1},
			{1,1,1,1,1},
			{0,1,2,2,0}
		},
	};

	int pattern3[3][5][5]
	{
		{
			{1,1,0,1,1},
			{2,2,1,1,1},
			{1,0,1,2,2},
			{1,1,2,0,1},
			{0,1,2,1,0}
		},
		{
			{1,0,1,1,1},
			{1,1,1,1,1},
			{1,1,2,2,0},
			{2,1,0,1,1},
			{2,1,2,1,0}
		},
		{
			{0,1,1,1,1},
			{1,1,2,1,1},
			{1,0,1,2,2},
			{0,1,2,2,0},
			{1,1,1,1,1}
		}
	};

};


struct BlockManager :public  GameObject
{
private:
	struct BlockGenerateData
	{
		std::vector<Vector3 > normal;
		std::vector<Vector3 > green;
		std::vector<Vector3 > black;
	};

	struct WaveData
	{
		Vector2 startSize;
		Vector4 color;
		std::vector<std::vector<int>> map;
		void Init(Vector2 startSize_, Vector4 color_);
	};

	BlockPatternData patternData;
	int const height = 3;
	std::vector<NormalBlock* >normalBlocks;
	std::vector<BlackBlock*> blackBlocks;
	std::vector<GreenBlock*> greenBlocks;
	std::vector<NormalBlock* > forUse;
	std::vector<GameObject* > usingBlocks;
	std::vector<NormalBlock* > addBlocks;

	Counter geneCnt;
	Counter moveCnt;
	Counter stopCnt;
	int const numAdd = 425;
	int const numUse = 125;
	float mapOkuZ;
	int rotateNum = 0;
	int cur_set = 0;
	int const maxSet = 3;

public:
	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	static constexpr float kBlockSize = 1.0f;
	static inline int const kNumNormalBlock = 550;
	static inline int const kNumBlackBlock = 30;
	static inline int const kNumGreenBlock = 20;
	static inline Vector3 const kStartPos = { 100,100,100 };
	static inline float curLastPosZ = kStartPos.z;
	static inline WaveData waveData[2];
	static inline int mapLast;
	static inline int isPerfect = false;
	static inline bool doGenerate = true;
	static inline std::vector<NormalBlock* > additions;
	static inline Counter addCnt;
	static inline bool doVanishRow = false;
	static inline int numFall = 0;

	void SetNormalBlock(NormalBlock* nomal_);
	void SetBlackBlock(BlackBlock* black_);
	void SetGreenBlock(GreenBlock* green_);

	BlockManager();
	static bool IsFall(float const z_);

private:
	void SetGround();
	void TurnBlocksIsActiveOff();
	void SetAdditions();
	void SetExceptAddtions();
	void AddBlockToLast();
	void GenerateBlocks();
	BlockGenerateData GetGenerateData();
	void MakeBlockToEnter();
	void MoveBlocks();
	bool CheckAllVanished();
	bool AddPerformance();
	bool CheckIsPerfect();
	void Vanish();
	bool CheckVanish();
};

