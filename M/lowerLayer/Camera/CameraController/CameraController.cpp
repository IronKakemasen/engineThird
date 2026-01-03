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
	CameraBufferPara cameraBufferPara;
	cameraBufferPara.cameraWorld = 
		cur_camera->Getter_Parameters()->trans.GetWorldPos();
	M::GetInstance()->SetCameraBufferPara(cameraBufferPara);
}

void CameraController::Update()
{
	cur_camera->Update();

	OverrideCameraBufferParameters();

#ifdef USE_IMGUI
	QuickChange();
#endif // 

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