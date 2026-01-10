#pragma once
#include "Transform.h"

struct CameraPara;

struct MainCamera
{
private:
	//各シーンに常備されているカメラのパラメータ
	CameraPara* cameraPara = nullptr;

public:
	//メインカメラ特有の処理
	void Init(CameraPara* CameraPara_);
	void Update();
	void Reset();
};

