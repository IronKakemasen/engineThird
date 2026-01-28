#pragma once
#include "../../../M/utilities/Counter/Counter.h"

struct CameraPara;

struct StageCamera
{


public:

	//各シーンに常備されているカメラのパラメータ
	CameraPara* cameraPara = nullptr;

	//メインカメラ特有の処理
	void Init(CameraPara* cameraPara_);
	void Update();
	void Reset();
};

