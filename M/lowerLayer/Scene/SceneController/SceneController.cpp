#include "SceneController.h"
#include "../SceneBehavior/SceneBehavior.h"
#include <assert.h>
#include "../../M.h"
#include "../FwdScenes.h"
#include "./UglyGrid/UglyGrid.h"


void SceneController::Debug()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

#ifdef USE_IMGUI
	static float deltaTime;
	deltaTime = ImGui::GetIO().Framerate;


	ImGui::Begin("SceneController" , nullptr, ImGuiWindowFlags_MenuBar);
	
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Select Scene"))
		{
			int i = 0;
			for (auto name : sceneNameContainer)
			{
				if (ImGui::MenuItem(name.c_str()))
				{
					nextScene = GetType(i);
				}
				++i;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text(GetName(runningScene).c_str());
	ImGui::DragFloat("deltaTime", &deltaTime);
	ImGui::Text("GridLine : "); ImGui::SameLine();
	ImGui::Checkbox(" ", &forDebug.doDrawGridLine);
	runSpeedChanger.AddDebug();
	ImGui::End();

	cur_Scene->gameObjManager->Debug();
	cur_Scene->cameraController->Debug();

	cur_Scene->Debug();

	if (forDebug.doDrawGridLine)
	{
		Matrix4* vpMat = &cur_Scene->cameraController->GetUsingCamera()->vpMat;
		UglyGrid::Draw(vpMat);
	}

#endif // USE_IMGUI

}

void SceneController::Update()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	Debug();

	cur_Scene->cameraController->Update();

	if (runSpeedChanger.AdjustRunSpeed())
	{
		cur_Scene->Update();
		cur_Scene->gameObjManager->Update();
	}

	Matrix4* vpMat = &cur_Scene->cameraController->GetUsingCamera()->vpMat;
	Matrix4 m = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
	cur_Scene->gameObjManager->Render(vpMat);

	cur_Scene->Draw();

	ChangeScene();

	Reset();
}

SceneController::SceneController(SceneType firstScene_)
{
	InstantiateScenes();
	Init(firstScene_);
}

void SceneController::Reset()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	if(cur_Scene->doReset) cur_Scene->Reset();
	cur_Scene->doReset = false;
}

void SceneController::Init(SceneType firstScene_)
{
	nextScene = firstScene_;
	runningScene = firstScene_;

	SetScenesToArray();
	for (auto* scene : allScene)
	{
		if (!scene)continue;

		scene->Instantiate();
		scene->Init();
		scene->gameObjManager->Init();
	}
}

void SceneController::SetScenesToArray()
{
	Set(kShikouteiScene, shikoScene.get());
	Set(kInGame, ingameScene.get());
	Set(kTitle, titleScene.get());
	Set(kModelView, modelViewScene.get());
	Set(kTutorial, tutorialScene.get());
}

void SceneController::InstantiateScenes()
{
	shikoScene.reset(new ShikouteiScene);
	ingameScene.reset(new InGameScene);
	titleScene.reset(new TitleScene);
	tutorialScene.reset(new TutorialScene);
	modelViewScene.reset(new ModelScene);
}


void SceneController::ChangeScene()
{
	runningScene = nextScene;
}

std::string SceneController::GetName(SceneType type_)
{
	std::string names[SceneType::kCount]
	{
		"ShikouteiScene",
		"InGame",
		"Title",
		"Tutorial",
		"ModelView",
	};

	return names[(int)type_];
}

SceneController::SceneType SceneController::GetType(int index_)
{
	SceneType types[SceneType::kCount]
	{
		kShikouteiScene,
		kInGame,
		kTitle,
		kTutorial,
		kModelView
	};

	return types[index_];
}


void SceneController::Set(SceneType type_, Scene* scene_)
{
	allScene[type_] = scene_;
	sceneNameContainer.emplace_back(GetName(type_));
}