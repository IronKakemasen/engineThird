#include "SceneController.h"
#include "../SceneBehavior/SceneBehavior.h"
#include <assert.h>
#include "../../../M.h"
#include "../FwdScenes.h"

void SceneController::Update()
{
	allScene[runningScene]->Debug();

	if (runSpeedChanger.AdjustRunSpeed())
	{
		allScene[runningScene]->Update();
	}

	allScene[runningScene]->Draw();
}


void SceneController::Init()
{
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		InstantiateScenes();
		SetScenesToArray();
		ChangeScene(SceneType::kSample);
	}

}

void SceneController::SetScenesToArray()
{
	allScene[SceneType::kSample] = sampleScene.get();

}

void SceneController::InstantiateScenes()
{
	sampleScene.reset(new SampleScene);
}


void SceneController::ChangeScene(SceneType startSceneType_)
{
	runningScene = startSceneType_;
}

