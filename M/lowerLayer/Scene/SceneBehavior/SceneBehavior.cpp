#include "SceneBehavior.h"
#include "../SceneController/SceneController.h"


SceneBehavior::SceneBehavior() 
{
	mainCamera.reset(new NormalCamera);
	cameraController.reset(new CameraController);
	cameraController->RegisterForContainer("mainCamera", mainCamera.get());
	cameraController->ChangeCamera("mainCamera");

	static bool onlyOnce = true;
	if (onlyOnce)
	{
		dirLight = M::GetInstance()->ImportDirLight();
		onlyOnce = false;
	}
}



