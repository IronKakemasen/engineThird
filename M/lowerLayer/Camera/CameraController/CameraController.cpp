#include "CameraController.h"
#include "../../M.h"
#include "../../engineCore/Buffer/constantBuffer/CameraParaBuffer/CameraParaBuffer.h"

CameraController::CameraController()
{

}

void CameraController::OverrideCameraParameters()
{
	CameraPara cameraPara;
	cameraPara.cameraWorld = cur_camera->Getter_Trans()->GetWorldPos();
	M::GetInstance()->SetCameraPara(cameraPara);
}

void CameraController::Update()
{
	cur_camera->Update();

	OverrideCameraParameters();
}

void CameraController::ChangeCamera(std::string dstCameraName_)
{
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
