#pragma once
#include <memory>
#include "../../Camera/NormalCamera/NormalCamera.h"
#include "../../Model/MobilePrimitive/MobileTriangle/MTriangle/MTriangle.h"
#include "../../Model/MobilePrimitive/MobileQuad/MQuad/MQuad.h"


class SceneBehavior
{
public:
	SceneBehavior();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;
	virtual void Debug() = 0;
protected:

	virtual void Instantiate() = 0;
	virtual void Init() = 0;

	std::unique_ptr< CameraBehavior > mainCamera;

};

