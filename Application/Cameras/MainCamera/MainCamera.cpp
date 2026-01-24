#include "MainCamera.h"
#include "../../M/lowerLayer/Camera/CameraBehavior.h"

void MainCamera::Init(CameraPara* cameraPara_, InGameController* ing_, Player* player_)
{
	cameraPara = cameraPara_;
	ing = ing_;
	player = player_;

	SetCameraActions(InGameController::Mode::kPlayable,
		std::make_unique<CameraActions::FollowPlayer>());

	SetCameraActions(InGameController::Mode::kEnter,
		std::make_unique<CameraActions::Enter>());

	SetCameraActions(InGameController::Mode::kUnPlayable,
		std::make_unique<CameraActions::UnPlayable>());

	SetCameraActions(InGameController::Mode::kResult,
		std::make_unique<CameraActions::Result>());

	SetCameraActions(InGameController::Mode::kGameOver,
		std::make_unique<CameraActions::GameOver>());

	for (auto& it : cameraActions)
	{
		it.second->Init(this);
	}
}


void MainCamera::Update()
{
	(*cameraActions[ing->curMode].get())();

}

void MainCamera::Reset()
{

}

void MainCamera::SetCameraActions(InGameController::Mode mode_,
	std::unique_ptr<CameraActions::Action > action_)
{
	cameraActions[mode_] = std::move(action_);
}

