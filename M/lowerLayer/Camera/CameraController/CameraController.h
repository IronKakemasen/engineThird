#pragma once
#include "../CameraBehavior.h"
#include <unordered_map>
#include <string>


class CameraController
{
	Camera* cur_camera = nullptr;
	std::unordered_map<std::string, Camera*> cameraContainer;
	void OverrideCameraParameters();

public:
	CameraController();
	void Update();
	void ChangeCamera(std::string dstCameraName_);
	void RegisterForContainer(std::string dstCameraName_, Camera* dstCamera_);
	Camera* GetUsingCamera();

};

