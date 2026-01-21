#include "./M/lowerLayer/engineCore/WinApp.h"
#include "./M/lowerLayer/M.h"
#include "M/lowerLayer/Scene/SceneController/SceneController.h"
#include "./M/lowerLayer/engineCore/Essential/leakChecker/leakChecker.h"

Quaternion SlerpQuaternion(Quaternion q1_, Quaternion q2_, float t_)
{
	Quaternion result;

	Quaternion q2 = q2_;
	q2.q = q2.GetNormalized();
	q1_.q = q1_.GetNormalized();

	float dot = q1_.GetDot(q2);
	Benri::Max(dot, 1.0f);

	//if (dot < 0.0)
	//{
	//	q2.q = q2.q * -1.0;
	//	dot = -dot;
	//}


	////非常に近い角度の場合の処理 (LERPへのフォールバック)
	//const float dotThreshold = 0.9995f;
	//if (dot > dotThreshold)
	//{
	//	Quaternion result;
	//	result.q = q1_.q + (q2.q + (q1_.q * -1.0)) * t_;
	//	result.q = result.GetNormalized();
	//	return result;
	//}

	//SLERPの計算
	float theta = std::acos(dot);
	float interpolatedTheta = theta * t_;
	float sinT0 = sinf(theta);
	float sinT1 = sinf(interpolatedTheta);

	float s1 = sinf((1.0f - t_) * theta) / sinT0;
	float s2 = sinT1 / sinT0;

	result.q = (q1_.q * s1) + (q2.q * s2);

	return result;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	////＜ポインタ破壊などを検知するためのもの＞
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

#ifdef _DEBUG
	//ResourceLeakChecker r;
#endif // DEBUG

	WinApp winApp((UINT)CommonV::kWindow_W, (UINT)CommonV::kWindow_H, L"ReadME");

	std::unique_ptr<SceneController> sceneController = 
		std::make_unique<SceneController>(SceneController::kShikouteiScene);


	Quaternion q1;
	q1.q = Quaternion ::CreateQuaternion({ 0.71f,0.71f,0.0f }, 0.3f,1); 
	Quaternion q2;
	q2.q = Quaternion::CreateQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f, 1);


	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		//Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			winApp.BeginFrame();

			M::GetInstance()->getPadState.Update();

			sceneController->Update();

			
			static Quaternion q3 = SlerpQuaternion(q1, q2, 0.0f);
			static Quaternion q4 = SlerpQuaternion(q1, q2, 0.0f);
			static Quaternion q5 = SlerpQuaternion(q1, q2, 0.0f);
			static Quaternion q6 = SlerpQuaternion(q1, q2, 0.0f);
			static Quaternion q7 = SlerpQuaternion(q1, q2, 0.0f);

			q3 = SlerpQuaternion(q1, q2, 0.0f);
			q4 = SlerpQuaternion(q1, q2, 0.3f);
			q5 = SlerpQuaternion(q1, q2, 0.5f);
			q6 = SlerpQuaternion(q1, q2, 0.7f);
			q7 = SlerpQuaternion(q1, q2, 1.0f);

			ImGui::Begin("Kadai");
			ImGui::DragFloat4("q3", reinterpret_cast<float*>(&q3.q));
			ImGui::DragFloat4("q4", reinterpret_cast<float*>(&q4.q));
			ImGui::DragFloat4("q5", reinterpret_cast<float*>(&q5.q));
			ImGui::DragFloat4("q6", reinterpret_cast<float*>(&q6.q));
			ImGui::DragFloat4("q7", reinterpret_cast<float*>(&q7.q));
			ImGui::End();



			winApp.EndFrame();

		}
	}

	winApp.TermApp();

    return 0;
}

