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

	//quad.Draw(vpMat);
	sprite.Draw(&ortho);
	M::GetInstance()->DrawEllipseWireFrame(
		{}, 2.0f, {}, { 255,255,255,255 }, vpMat);
}

void ShikouteiScene::Reset()
{

}

void ShikouteiScene::Debug()
{
#ifdef USE_IMGUI



#endif // USE_IMGUI

}

