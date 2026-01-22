#include "ShikouteiScene.h"
#include "../../M/utilities/Json/Json.h"


void ShikouteiScene::Update()
{
	//アトラス画像の更新
	atlasNumber.Update();
	//実践
	static Counter timer(1.0f);
	static float timeNum;
	timer.Add();
	if(timer.IsEnd())
	{ 
		timeNum++;
		Benri::AdjustMax(timeNum, 9.0f, 0.0f);
	}
	atlasNumber.ChangeAtlasIndex(timeNum);


	if (M::GetInstance()->IsKeyTriggered(KeyType::R))
	{
		SceneBehavior::doReset = true;
	}
}

void ShikouteiScene::Draw()
{
	//現在使用しているカメラのビュープロジェクション
	Matrix4* vpMat = &cameraController->GetUsingCamera()->vpMat;
	//平行投影用
	Matrix4 ortho = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);

	//矩形の描画
	quad.Draw(vpMat);
	//スプライトの描画
	sprite.Draw(&ortho);
	//円のワイヤーフレームの描画
	M::GetInstance()->DrawEllipseWireFrame(
		{}, 2.0f, {}, { 255,255,255,255 }, vpMat);
	//アトラス画像の描画
	atlasNumber.Draw(&ortho);

}

void ShikouteiScene::Reset()
{

}

void ShikouteiScene::Debug()
{


}


