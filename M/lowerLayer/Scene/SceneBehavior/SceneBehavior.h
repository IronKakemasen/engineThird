#pragma once
#include <memory>
#include "../../Camera/NormalCamera/NormalCamera.h"
#include "../../Camera/CameraController/CameraController.h"
#include "../../Model/MobilePrimitive/MobileTriangle/MTriangle/MTriangle.h"
#include "../../Model/MobilePrimitive/MobileQuad/MQuad/MQuad.h"

class DirectionalLight;


class SceneBehavior
{
public:
	SceneBehavior();

	std::unique_ptr < CameraController > cameraController;
	std::unique_ptr< NormalCamera > mainCamera;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;
	virtual void Debug() = 0;

protected:
	static inline DirectionalLight* dirLight = nullptr;

	virtual void Instantiate() = 0;
	virtual void Init() = 0;

};

