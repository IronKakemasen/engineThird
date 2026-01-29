#include "SceneController.h"
#include "../SceneBehavior/SceneBehavior.h"
#include <assert.h>
#include "../../M.h"
#include "../FwdScenes.h"
#include "./UglyGrid/UglyGrid.h"
#include "../engineCore/Light/PointLight/PointLight.h"

void SceneController::Draw()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	Matrix4* vpMat = &cur_Scene->cameraController->GetUsingCamera()->vpMat;
	Matrix4 orthoMat = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	cur_Scene->Draw();
	cur_Scene->gameObjManager->Render(vpMat);

#ifdef _DEBUG
	if (forDebug.doDrawGridLine)
	{
		UglyGrid::Draw(vpMat);
		axisModel->Draw(vpMat);
	}

	cur_Scene->cameraController->DrawDebugUI(&orthoMat);

	#endif
}
void SceneController::Debug()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

#ifdef USE_IMGUI

	axisModel->MakeAllPartsBeChildren(
		&cur_Scene->cameraController->GetUsingCamera()->Getter_Parameters()->trans);
	for (auto a = axisModel->model->GetAppearance()->begin();
		a != axisModel->model->GetAppearance()->end(); ++a)
	{
		a->trans.lookDir = cur_Scene->cameraController->GetUsingCamera()->
			Getter_Parameters()->trans.lookDir;
	}

	static float fps;
	fps = ImGui::GetIO().Framerate;

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

	if (M::GetInstance()->IsKeyTriggered(KeyType::G))
	{
		forDebug.doDrawGridLine = !forDebug.doDrawGridLine;
	}

	ImGui::Text(GetName(runningScene).c_str());
	ImGui::Text("FPS : %.2f ", fps); 
	ImGui::Text("GridLine : "); ImGui::SameLine();
	ImGui::Checkbox("(G)", &forDebug.doDrawGridLine);
	runSpeedChanger.AddDebug();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("PostEffect"))
		{
			if (ImGui::MenuItem("NoEffection"))
			{
				M::GetInstance()->ChangePostEffect(PostEffectType::kNone);
			}
			if (ImGui::MenuItem("MonoChrome"))
			{
				M::GetInstance()->ChangePostEffect(PostEffectType::kGreyScale);
			}
			if (ImGui::MenuItem("NeonLike"))
			{
				M::GetInstance()->ChangePostEffect(PostEffectType::kSimpleNeonLike);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	if (ImGui::TreeNode("DirectionalLight"))
	{
		ImGui::DragFloat3("Pos", reinterpret_cast<float*>(&cur_Scene->dirLight->Getter_Para()->pos), 0.1f);
		ImGui::DragFloat("intensity", reinterpret_cast<float*>(&cur_Scene->dirLight->Getter_Para()->intensity), 0.1f);
		ImGui::TreePop();
	}

	ImGui::End();

	cur_Scene->gameObjManager->Debug();
	cur_Scene->cameraController->Debug();
	cur_Scene->Debug();


	if (runSpeedChanger.IsStop())
	{
		//cur_Scene->dirLight->Getter_Para()->color =
		//	{ 5,5,5};
	}
	else
	{
		cur_Scene->dirLight->Getter_Para()->color =
			forDebug.lightBuffer;
	}

#endif // USE_IMGUI

}

void SceneController::Update()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	if (!cur_Scene->doReset)
	{

		if (runSpeedChanger.AdjustRunSpeed())
		{
			cur_Scene->gameObjManager->Update();
			cur_Scene->Update();
		}

		cur_Scene->cameraController->Update();

		Debug();
	}

	Reset();
	ChangeScene();

}

SceneController::SceneController(SceneType firstScene_)
{
	InstantiateScenes();
	Init(firstScene_);
}

void SceneController::Reset()
{
	SceneBehavior* cur_Scene = allScene[runningScene];

	if (cur_Scene->doReset)
	{
		cur_Scene->Reset();
		cur_Scene->gameObjManager->Reset();
	}

	cur_Scene->doReset = false;
}

void SceneController::Init(SceneType firstScene_)
{
	nextScene = firstScene_;
	runningScene = firstScene_;

	SetScenesToArray();
	int i = 0;
	for (auto* scene : allScene)
	{
		if (!scene)continue;

		scene->Instantiate();
		scene->Init();
		scene->gameObjManager->Init();
		scene->nextScene = SceneType(i);
		i++;
	}

	axisModel->Init(nullptr);

#ifdef _DEBUG
	forDebug.lightBuffer = allScene[runningScene]->dirLight->Getter_Para()->color;
	
#endif // _DEBUG


}

void SceneController::SetScenesToArray()
{
	Set(kShikouteiScene, shikoScene.get());
	Set(kInGame, ingameScene.get());
	Set(kTitle, titleScene.get());
	Set(kTutorial, tutorialScene.get());
	Set(kModelView, modelViewScene.get());
	Set(kStageSelect, stageSelectScene.get());
}

void SceneController::InstantiateScenes()
{
	shikoScene.reset(new ShikouteiScene);
	ingameScene.reset(new InGameScene);
	titleScene.reset(new TitleScene);
	tutorialScene.reset(new TutorialScene);
	modelViewScene.reset(new ModelScene);
	stageSelectScene.reset(new StageSelectScene);
	axisModel.reset(new AxisModel);
}


void SceneController::ChangeScene()
{
	Scene* cur_Scene = allScene[runningScene];
	if (runningScene != cur_Scene->SendSignal())
	{
		nextScene = cur_Scene->SendSignal();
		cur_Scene->nextScene = runningScene;
		cur_Scene->doReset = true;
	}

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
		"StageSelect"
	};

	return names[(int)type_];
}

SceneType SceneController::GetType(int index_)
{
	SceneType types[SceneType::kCount]
	{
		kShikouteiScene,
		kInGame,
		kTitle,
		kTutorial,
		kModelView,
		kStageSelect
	};

	return types[index_];
}


void SceneController::Set(SceneType type_, Scene* scene_)
{
	allScene[type_] = scene_;
	sceneNameContainer.emplace_back(GetName(type_));
}

void SceneController::ChangeScene(SceneType nextSceneType_)
{
	nextScene = nextSceneType_;
}