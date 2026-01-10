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
		cur_Scene->cameraController->Update();
		cur_Scene->gameObjManager->Update();
	}

	Matrix4* vpMat = &cur_Scene->cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
	cur_Scene->gameObjManager->Render(vpMat);

	cur_Scene->Draw();

	Reset();
}

void SceneController::Reset()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	if(cur_Scene->doReset) cur_Scene->Reset();
	cur_Scene->doReset = false;
}

void SceneController::Init()
{
	static bool initOnlyOnce = true;

	if (initOnlyOnce)
	{
		initOnlyOnce = false;
		InstantiateScenes();
		SetScenesToArray();
		ChangeScene(SceneType::kShikouteiScene);
		for (auto* scene : allScene)
		{
			if (!scene)continue;

			scene->Instantiate();
			scene->Init();
		}
	}

}

void SceneController::SetScenesToArray()
{
	allScene[SceneType::kShikouteiScene] = shikoScene.get();

}

void SceneController::InstantiateScenes()
{
	shikoScene.reset(new ShikouteiScene);
}


void SceneController::ChangeScene(SceneType startSceneType_)
{
	runningScene = startSceneType_;
}

