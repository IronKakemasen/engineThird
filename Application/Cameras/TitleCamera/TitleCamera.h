#pragma once

#include "../../../M/utilities/Counter/Counter.h"
#include "../../GameObjects/InGameController/InGameController.h"

struct CameraPara;
struct InGameController;
struct Player;

struct TitleCamera
{
private:


	Vector3 fstPos = { 0.348f,0.596f,18.189f };
	Vector3 fstLookDir = { -0.591f,0.282f,0.756f };
	Vector3 secLookDir = { 0.4f,-0.461f,-0.793f };
	Vector3 secPos = { -1.9f,2.47f,22.4f };
	Vector3 thirdPos = { 0,75,150 };

public:

	//各シーンに常備されているカメラのパラメータ
	CameraPara* cameraPara = nullptr;

	//メインカメラ特有の処理
	void Init(CameraPara* CameraPara_);
	void Update();
	void Reset();
};

