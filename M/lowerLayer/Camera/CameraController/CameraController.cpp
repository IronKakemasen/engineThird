#include "CameraController.h"
#include "../../M.h"
#include "../../engineCore/Buffer/constantBuffer/CameraParaBuffer/CameraParaBuffer.h"

#ifdef USE_IMGUI
#include "imgui.h"
#endif // USE_IMGUI

void CameraController::Debug()
{

#ifdef USE_IMGUI
	static int switches = 0;

	ImGui::Begin("CameraController", nullptr, ImGuiWindowFlags_MenuBar);		
	int i = 0;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Select Camera"))
		{
			for (const auto& [name, camera] : cameraContainer)
			{
				if (ImGui::MenuItem(name.c_str()))
				{
					ChangeCamera(name);
				}
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	auto* para = cur_camera.first->Getter_Parameters();
	ImGui::Text(("CURRENT " + cur_camera.second).c_str());
	ImGui::DragFloat3("Pos ", reinterpret_cast<float*>(&para->trans.pos), 0.1f);
	ImGui::DragFloat3("LookDir ", reinterpret_cast<float*>(&para->trans.lookDir), 0.025f);
	ImGui::DragFloat("FOV ", &para->fov, 0.01f);
	ImGui::SliderFloat("InterpolateCoe", &para->trans.interpolationCoe, 0.0f, 1.0f);
	ImGui::Text("QuickChange : C ");

	if (cur_camera.second == "debugCamera")
	{
		ImGui::Text("MoveKeys : ArrowKeys , Z , X ");
	}


	ImGui::End();

#endif // USE_IMGUI

}

CameraController::CameraController()
{
	debugCamera.reset(new DebugCamera);
	RegisterForContainer("debugCamera", debugCamera.get());
	preCamera = std::make_pair(debugCamera.get(), "debugCamera");
}

void CameraController::OverrideCameraBufferParameters()
{
	CameraBufferPara cameraBufferPara;
	cameraBufferPara.cameraWorld = 
		cur_camera.first->Getter_Parameters()->trans.GetWorldPos();
	M::GetInstance()->SetCameraBufferPara(cameraBufferPara);
}

void CameraController::Update()
{
	cur_camera.first->Update();

	OverrideCameraBufferParameters();

	QuickChange();

}

void CameraController::ChangeCamera(std::string dstCameraName_)
{
	if (cur_camera.first)
	{
		if(preCamera != cur_camera)	preCamera = cur_camera;

	}

	cur_camera = std::make_pair(cameraContainer[dstCameraName_], dstCameraName_);
}

void CameraController::RegisterForContainer(std::string dstCameraName_, Camera* dstCamera_)
{
	cameraContainer[dstCameraName_] = dstCamera_;
}

Camera* CameraController::GetUsingCamera()
{
	return cur_camera.first;
}

DebugCamera* CameraController::GetDebugCamera()
{
	return debugCamera.get();
}

Camera* CameraController::GetMainCamera()
{
	return cameraContainer["mainCamera"];
}

void CameraController::QuickChange()
{
#ifdef _DEBUG

	if (M::GetInstance()->IsKeyTriggered(KeyType::C))
	{
		std::pair<Camera*, std::string > buff = cur_camera;
		cur_camera = preCamera;
		preCamera = buff;
	}

#endif // _DEBUG

}

//if (ImGui::TreeNode((*itr)->Getter_Name().c_str()))
//{
//	ImGui::DragFloat3("pos", reinterpret_cast<float*>(&(*itr)->Getter_Trans()->pos), 0.1f);
//	ImGui::TreePop();
//}
