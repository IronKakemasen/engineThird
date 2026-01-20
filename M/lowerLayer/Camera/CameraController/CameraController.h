#pragma once
#include "../DebugCamera/DebugCamera.h"
#include "Sprite.h"
#include <unordered_map>
#include <string>
#include <memory>

class CameraController
{
	std::pair<Camera*, std::string > cur_camera;
	std::pair<Camera*, std::string > preCamera;
	std::unique_ptr<DebugCamera> debugCamera;
	std::unordered_map<std::string, Camera*> cameraContainer;
	Sprite sprite_debug;
	void OverrideCameraBufferParameters();
	void QuickChange();

public:
	CameraController();
	void Update();
	void ChangeCamera(std::string dstCameraName_);
	void RegisterForContainer(std::string dstCameraName_, Camera* dstCamera_);
	void Debug();
	void DrawDebugUI(Matrix4* orthoMat_);
	Camera* GetUsingCamera();
	Camera* GetMainCamera();
	DebugCamera* GetDebugCamera();
};

