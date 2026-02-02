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
	float const adjustMul = 2.0f;

	auto X = M::GetInstance()->getPadState.GetRightStick(0).x;
	auto Y = M::GetInstance()->getPadState.GetRightStick(0).y;
	if (std::abs(X) < 0.3f)X = 0.0f;
	if (std::abs(Y) < 0.3f)Y = 0.0f;

	Vector3 tmp = Vector3{ X,0,Y }.GetNormalized();

	camera->cameraPara->trans.pos =
		Easing::EaseOutCubic(camera->cameraPara->trans.pos, nextPos + tmp * adjustMul,
			kDefaultFollowCoe)+ offsetDebug ;

#ifdef _DEBUG
	auto* m = M::GetInstance();
	float const speed = 0.01f;
	if (m->IsKeyPressed(KeyType::J))offsetDebug.x -= speed ;
	if (m->IsKeyPressed(KeyType::L))offsetDebug.x += speed ;
	if (m->IsKeyPressed(KeyType::I))offsetDebug.z += speed ;
	if (m->IsKeyPressed(KeyType::K))offsetDebug.z -= speed ;
	if (m->IsKeyTriggered(KeyType::ESCAPE))offsetDebug = {};

#endif // _DEBUG

	camera->cameraPara->trans.lookDir = kPlayableDefaultLookDir ;

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
