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


