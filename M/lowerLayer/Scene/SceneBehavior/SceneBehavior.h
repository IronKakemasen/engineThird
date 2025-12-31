#pragma once
#include <memory>
#include "../../Camera/NormalCamera/NormalCamera.h"
#include "../../Camera/CameraController/CameraController.h"
#include "../../engineCore/Light/DirectionalLight/DirectionalLight.h"
#include "../../engineCore/Light/PointLight/PointLight.h"
#include "../../GameObjectManager/GameObjectManager.h"

#ifdef USE_IMGUI
#include "../../../../external/imgui/imgui.h"
#endif // USE_IMGUI



class SceneBehavior
{
public:
	SceneBehavior();

	std::unique_ptr < CameraController > cameraController;
	std::unique_ptr< NormalCamera > mainCamera;
	std::unique_ptr< GameObjectManager > gameObjManager;
	DirectionalLight* dirLight = nullptr;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;
	virtual void Debug() = 0;

protected:

	virtual void Instantiate() = 0;
	virtual void Init() = 0;

};

