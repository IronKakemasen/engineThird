#pragma once
#include "../../M/lowerLayer/GameObject/GameObjectBehavior.h"
#include "Controllers.h"
#include <unordered_map>

struct InGameController : GameObject
{
	enum Mode
	{
		kEnter,
		kPlayable,
		kDeath,
		kClear,
		kResult,
		kCount
	};

	GameController::Enter enter;
	GameController::Playable playable;
	GameController::Death death;
	GameController::Result result;
	GameController::Clear clear;

public:

	std::unordered_map<Mode,GameController::ControllBehavior*>
		behaviors;

	static inline int cur_wave = 0;
	static inline int cur_phase = 0;

	static int const numStage = 2;
	static inline Mode mode = kEnter;
	static inline float cur_cnt;
	static inline bool canChangeMode = false;

	virtual void Update()override;
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Draw(Matrix4* vpMat_)override;
	virtual void SetCollisionBackTable()override;

	static std::string CurMode();
	bool doReset = false;
	InGameController();

};

