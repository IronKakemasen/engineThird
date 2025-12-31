#include "SceneBehavior.h"
#include "../SceneController/SceneController.h"


SceneBehavior::SceneBehavior() 
{
	gameObjManager.reset(new GameObjectManager);
	mainCamera.reset(new NormalCamera);
	cameraController.reset(new CameraController);
	cameraController->RegisterForContainer("mainCamera", mainCamera.get());
	cameraController->ChangeCamera("mainCamera");
	dirLight = M::GetInstance()->ImportDirLight();
}



