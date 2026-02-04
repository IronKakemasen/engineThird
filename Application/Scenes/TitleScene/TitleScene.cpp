#include "TitleScene.h"

void TitleScene::Update()
{
	dirLight->Getter_Para()->pos = { 1,-1,1 };

	ImGui::Begin("jjj");
	ImGui::DragFloat3("c1", reinterpret_cast<float*>(&pLights[0]->Getter_Para()->color));
	ImGui::DragFloat3("c2", reinterpret_cast<float*>(&pLights[1]->Getter_Para()->color));
	ImGui::End();

	titleCamera.Update();

	if (M::GetInstance()->getPadState.IsJustPressed(0, PAD_A) ||
		M::GetInstance()->getPadState.IsJustPressed(0, PAD_RB))
	{
		pushed = true;
	}
	else if (M::GetInstance()->IsKeyTriggered(KeyType::SPACE))
	{
		pushed = true;
	}
	if (c.count<=0.2f)
	{
		c.Add();
		Benri::Max(c.count, 0.2f);
	}

	if (pushed)
	{
		c.Add();

		if (c.IsEnd())
		{
			pushed = false;
			ChangeScene(SceneType::kStageSelect);
		}
	}

}

void TitleScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

}

void TitleScene::Reset()
{

}

void TitleScene::Debug()
{
#ifdef USE_IMGUI



#endif // USE_IMGUI

}

