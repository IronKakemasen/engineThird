#pragma once
#include "../DebugCamera/DebugCamera.h"
#include <unordered_map>
#include <string>
#include <memory>

class CameraController
{
	Camera* cur_camera = nullptr;
	Camera* preCamera = nullptr;
	std::unique_ptr<DebugCamera> debugCamera;
	std::unordered_map<std::string, Camera*> cameraContainer;

	void OverrideCameraBufferParameters();

public:
	CameraController();
	void Update();
	void ChangeCamera(std::string dstCameraName_);
	void RegisterForContainer(std::string dstCameraName_, Camera* dstCamera_);
	Camera* GetUsingCamera();
	void QuickChange();
};

