#include "CameraActions.h"
#include "MainCamera.h"
#include "../../GameObjects/Player/Player.h"
#include "../../M/lowerLayer/Camera/CameraBehavior.h"


void CameraActions::ActionBehavior::Init(MainCamera* camera_)
{
	camera = camera_;
}


void CameraActions::FollowPlayer::operator()()
{
	Vector3 nextPos = camera->player->Getter_Trans()->GetWorldPos() + offsetFollow;

	camera->cameraPara->trans.pos =
		Easing::EaseOutCubic(camera->cameraPara->trans.pos, nextPos, kDefaultFollowCoe);

	camera->cameraPara->trans.lookDir = kPlayableDefaultLookDir;

}

void CameraActions::FollowPlayer::Reset()
{

}

void CameraActions::Enter::operator()()
{

}

void CameraActions::Enter::Reset()
{

}

void CameraActions::UnPlayable::operator()()
{
}

void CameraActions::UnPlayable::Reset()
{

}

void CameraActions::GameOver::operator()()
{

}

void CameraActions::GameOver::Reset()
{

}

void CameraActions::Result::operator()()
{

}

void CameraActions::Result::Reset()
{

}
