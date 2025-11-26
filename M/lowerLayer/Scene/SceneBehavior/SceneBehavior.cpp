#include "SceneBehavior.h"
#include "../SceneController/SceneController.h"


SceneBehavior::SceneBehavior() 
{
	drawExecutor.reset(new DrawExecutor);
	mainCamera.reset(new NormalCamera);
	
}

//DrawExecutorにドロー関数を登録する
void SceneBehavior::RegisterForDrawExecutor(CommonDrawingSystem* dst_)
{
	drawExecutor->Register(dst_);

}

void SceneBehavior::DrawAllRegistered(Matrix4* vpMat_)
{
	drawExecutor->Setter_ViewProjMat(vpMat_);
	drawExecutor->DrawRegistered();

}

