#include "./M/lowerLayer/engineCore/WinApp.h"
#include "./M/M.h"
#include "./M/utilities/MobilePrimitive/MobileTriangle/TriangleM/TriangleM.h"
#include "./M/utilities/Camera/NormalCamera/NormalCamera.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	////＜ポインタ破壊などを検知するためのもの＞
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

    WinApp winApp((UINT)V_Common::kWindow_W, (UINT)V_Common::kWindow_H, L"Title");
	TriangleM tM;
	tM.Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	NormalCamera camera;
	camera.trans.translate = { 0,0,-1.0f };

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

			camera.Update();

			ImGui::Begin("AA");
			ImGui::DragFloat3("camera", reinterpret_cast<float*>(&camera.trans.translate),0.01f);
			ImGui::DragFloat3("poly", reinterpret_cast<float*>(&tM.trans.translate), 0.01f);
			ImGui::End();

			tM.Draw(camera.vpMat);

			winApp.EndFrame();

		}



	}



	winApp.TermApp();

    return 0;
}

