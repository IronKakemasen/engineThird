#include "SceneController.h"
#include "../SceneBehavior/SceneBehavior.h"
#include <assert.h>
#include "../../M.h"
#include "../FwdScenes.h"

void SceneController::Update()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	cur_Scene->Debug();

	if (runSpeedChanger.AdjustRunSpeed())
	{
		cur_Scene->Update();
	}

	cur_Scene->Draw();
}


void SceneController::Init()
{
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		InstantiateScenes();
		SetScenesToArray();
		ChangeScene(SceneType::kInGame);
	}

}

void SceneController::SetScenesToArray()
{
	allScene[SceneType::kSample] = sampleScene.get();
	allScene[SceneType::kInGame] = inGameScene.get();
	allScene[SceneType::kTitle] = titleScene.get();

}

void SceneController::InstantiateScenes()
{
	inGameScene.reset(new InGameScene);
	titleScene.reset(new TitleScene);
	sampleScene.reset(new SampleScene);
}


void SceneController::ChangeScene(SceneType startSceneType_)
{
	runningScene = startSceneType_;
}

