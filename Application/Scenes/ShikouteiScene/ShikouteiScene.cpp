#include "ShikouteiScene.h"

void ShikouteiScene::Update()
{

}

void ShikouteiScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void ShikouteiScene::Reset()
{

}

void ShikouteiScene::Debug()
{
#ifdef USE_IMGUI
	ImGui::Begin("ShikouteiScene Scene Debug");
	ImGui::Text("PlayerScaleX: %.2f", player->Getter_Trans()->scale.x);
	ImGui::End();


#endif // USE_IMGUI

}

