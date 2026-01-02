#include "CameraController.h"
#include "../../M.h"
#include "../../engineCore/Buffer/constantBuffer/CameraParaBuffer/CameraParaBuffer.h"

CameraController::CameraController()
{
	debugCamera.reset(new DebugCamera);
	RegisterForContainer("debugCamera", debugCamera.get());
	preCamera = debugCamera.get();
}

void CameraController::OverrideCameraBufferParameters()
{
	CameraPara cameraPara;
	cameraPara.cameraWorld = cur_camera->Getter_Trans()->GetWorldPos();
	M::GetInstance()->SetCameraPara(cameraPara);
}

void CameraController::Update()
{
	cur_camera->Update();

	OverrideCameraBufferParameters();
	QuickChange();
}

void CameraController::ChangeCamera(std::string dstCameraName_)
{
	if (cur_camera)
	{
		preCamera = cur_camera;
	}
	cur_camera = cameraContainer[dstCameraName_];
}

void CameraController::RegisterForContainer(std::string dstCameraName_, Camera* dstCamera_)
{
	cameraContainer[dstCameraName_] = dstCamera_;
}

Camera* CameraController::GetUsingCamera()
{
	return cur_camera;
}

void CameraController::QuickChange()
{
	if (M::GetInstance()->IsKeyTriggered(KeyType::C))
	{
		Camera* buff = cur_camera;
		cur_camera = preCamera;
		preCamera = buff;
	}
}