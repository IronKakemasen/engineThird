#include "InGameController.h"

void InGameController::Update()
{
	(*behaviors[mode])(this);
}

void InGameController::Init()
{

}

void InGameController::Reset()
{

}

void InGameController::Draw(Matrix4* vpMat_)
{

}

InGameController::InGameController()
{
	behaviors[kEnter] = &enter;
	behaviors[kPlayable] = &playable;
	behaviors[kResult] = &result;
	behaviors[kDeath] = &death;
	behaviors[kClear] = &clear;

}

