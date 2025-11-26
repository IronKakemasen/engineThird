#pragma once
#include <memory>
#include "../../DrawExecutor/DrawExecutor.h"
#include "../../Camera/NormalCamera/NormalCamera.h"
#include "../../../utilities/MobilePrimitive/MobileTriangle/MTriangle/MTriangle.h"
#include "../../../utilities/MobilePrimitive/MobileQuad/MQuad/MQuad.h"


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
	std::unique_ptr< DrawExecutor >drawExecutor;
	void RegisterForDrawExecutor(CommonDrawingSystem* dst_);
	void DrawAllRegistered(Matrix4* vpMat_);

};

