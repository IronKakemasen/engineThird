#include "./M/lowerLayer/engineCore/WinApp.h"
#include "./M/lowerLayer/M.h"
#include "M/lowerLayer/Scene/SceneController/SceneController.h"
#include "./M/lowerLayer/engineCore/Essential/leakChecker/leakChecker.h"
#include "../../utilities/Json/Json.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	////＜ポインタ破壊などを検知するためのもの＞
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

#ifdef _DEBUG
	//ResourceLeakChecker r;
#endif // DEBUG

	WinApp winApp((UINT)CommonV::kWindow_W, (UINT)CommonV::kWindow_H, L"ReadME");
	Json::LoadAll("./resource/application/json/");


	// resource/application/json 以下データをロード
	Json::LoadAll("./resource/application/json/");

	std::unique_ptr<SceneController> sceneController =
		std::make_unique<SceneController>(kStageSelect);

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
			winApp.OffScreenBegin();

			sceneController->Update();
			sceneController->Draw();

			winApp.OffScreenEnd();

		}
	}

	winApp.TermApp();

    return 0;
}

