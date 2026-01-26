#pragma once
#include "../../../M/utilities/Counter/Counter.h"
#include "../../GameObjects/InGameController/InGameController.h"
#include "CameraActions.h"
#include <unordered_map>
#include <memory>

struct CameraPara;
struct InGameController;
struct Player;

struct MainCamera
{
private:

	std::unordered_map<InGameController::Mode, 
		std::unique_ptr<CameraActions::Action>> cameraActions;

	void SetCameraActions(InGameController::Mode mode_, 
		std::unique_ptr<CameraActions::Action > action_);

public:

	//各シーンに常備されているカメラのパラメータ
	CameraPara* cameraPara = nullptr;
	InGameController* ing = nullptr;
	Player* player = nullptr;

	//メインカメラ特有の処理
	void Init(CameraPara* CameraPara_, InGameController* ing_, Player* player_);
	void Update();
	void Reset();
};

