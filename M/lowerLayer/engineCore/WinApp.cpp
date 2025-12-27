#include "WinApp.h"
#include "./Essential/BarrierControl/BarrierControl.h"
#include <assert.h>
#include "./PSO/pipelineCreators/pipelineCreators.h"
#include "../M.h"
//#include <timeapi.h>

bool WinApp::InitD3D()
{
	//COMの初期化
	CoInitializeEx(0, COINITBASE_MULTITHREADED);

	log = DebugLogInitialize();

	//デバイス
	deviceSetUp.Initialize();

	//[ デバッグヘルパー ]	
	//誰も捕捉しなかった場合に(Unhandled)、補足する関数を登録
	SetUnhandledExceptionFilter(ExportDump);

	//コンパイラーの初期化
	dxCompile.Initialize();

	//シェーダーテーブルの設定
	vpShaders.Init(&dxCompile);

	//コマンドキュー
	commandControl.MakeCommandQueue(deviceSetUp.Getter_Device());

	//rtv、srv、dsvそれぞれのdescriptorHeapを作成する
	rtvDescHeap.Init(deviceSetUp.Getter_Device(), 2);
	srvDescHeap.Init(deviceSetUp.Getter_Device(), 64);
	dsvDescriptorHeap.Init(deviceSetUp.Getter_Device(), 1);

	//swapChainの設定
	swapChainControl.Initialize(
		&m_hWnd, commandControl.Getter_CommandQueue(), deviceSetUp.Getter_DxgiFactory(),
		deviceSetUp.Getter_Device(), &rtvDescHeap,&dsvDescriptorHeap);

	//コマンドアローケータの生成
	commandControl.MakeCommandAllocator(deviceSetUp.Getter_Device());

	//コマンドリストの生成
	commandControl.MakeCommandList(deviceSetUp.Getter_Device());

	//FenceControl
	fenceControl.Initialize(deviceSetUp.Getter_Device(), deviceSetUp.Getter_DxgiFactory());

	//pipelineSetの初期化
	allPipelineSet.Initialize(deviceSetUp.Getter_Device(), &vpShaders, commandControl.Getter_commandList());
	
	//srvCreatorの初期化
	srvCreator.Init(&srvDescHeap,deviceSetUp.Getter_Device(),&commandControl , &shaderBufferData);

	//textureDataManager,textureDataCreatorの初期化
	textureDataManager.Init(srvCreator.Getter_TextureSrvCreator());

	//meshCreatorの初期化
	meshCreator.Init(&allPipelineSet, deviceSetUp.Getter_Device(),
		&textureDataManager,&commandControl,&fenceControl,swapChainControl.Getter_SwapChain());

	//lightCreatorの初期化
	lightCreator.Init(&exclusiveDraw, deviceSetUp.Getter_Device());

	//cameraParameterSetterの初期化
	cameraParameterSetter.Init(deviceSetUp.Getter_Device());

	//exclusiveDrawの初期化
	exclusiveDraw.Init(&allPipelineSet, &allMesh, 
		&shaderBufferData, cameraParameterSetter.Getter_Buffer());


#ifdef USE_IMGUI
	//ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX12_Init(
		deviceSetUp.Getter_Device(),
		swapChainControl.Ref_SwapChainDesc().BufferCount,
		swapChainControl.Ref_RenderTargetDesc().Format,
		srvDescHeap.Getter_Descriptorheap(),
		srvDescHeap.Getter_Descriptorheap()->GetCPUDescriptorHandleForHeapStart(),		
		srvDescHeap.Getter_Descriptorheap()->GetGPUDescriptorHandleForHeapStart());

	ShaderBuffer::cur_index++;

#endif

	//メッシュの初期化、生成
	allMesh.Init(deviceSetUp.Getter_Device(), srvCreator.Getter_ParticleMeshSrvCreator(),&allPipelineSet);

	return true;
}

void WinApp::BeginFrame()
{
	QueryPerformanceFrequency(&fpsController.mTimeFreq);
	QueryPerformanceCounter(&fpsController.mTimeStart);

	//Imguiにここからフレームが始まる旨を告げる
#ifdef USE_IMGUI
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif

	// コマンドの記録を開始.
	commandControl.PrepareForNextCommandList();

	//バリア
	D3D12_RESOURCE_BARRIER barrier = BarrierControl::Create(
		swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->Getter_Resource(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

	//TransitionBarrierを張る
	BarrierControl::Pitch(commandControl.Getter_commandList(), &barrier);

	// レンダーゲットの設定.
	commandControl.Getter_commandList()->OMSetRenderTargets(1,
		swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->Getter_Handle(), false,
		swapChainControl.Getter_DepthBuffer()->Getter_Handle());
	//CommandControl.Getter_commandList()->OMSetRenderTargets(1,
	//	SwapChainControl.Getter_ColorBuffer(SwapChainControl.frameIndex)->Getter_Handle(), FALSE, nullptr);

	
	//指定した深度で画面クリアする
	commandControl.Getter_commandList()->ClearDepthStencilView(*swapChainControl.Getter_DepthBuffer()->Getter_Handle(),
		D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//指定した色で画面全体をクリアする
	commandControl.Getter_commandList()->ClearRenderTargetView(
		*swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->Getter_Handle(), windowColor, 0, nullptr);

	////描画用のDescriptorHeapの設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescHeap.Getter_Descriptorheap()};
	commandControl.Getter_commandList()->SetDescriptorHeaps(1, descriptorHeaps);

	//DXの行列の設定
	commandControl.Getter_commandList()->RSSetViewports(1,
		swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->Getter_ViewportMatrix());

	commandControl.Getter_commandList()->RSSetScissorRects(1,
		swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->ScissorRect());


}

void WinApp::EndFrame()
{
	//drawIndexをリセットする
	exclusiveDraw.ResetDrawIndexes();

	//[ 画面に書く処理が終わり、画面に映すので状態を遷移 ]

#ifdef USE_IMGUI
	ImGui::Render();
	//実際のcommandListのImguiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandControl.Getter_commandList());
#endif

	//バリア
	//RenderTarget->Prsent
	D3D12_RESOURCE_BARRIER barrier = BarrierControl::Create(
		swapChainControl.Getter_ColorBuffer(swapChainControl.frameIndex)->Getter_Resource(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

	//TransitionBarrierを張る
	BarrierControl::Pitch(commandControl.Getter_commandList(), &barrier);

	//コマンドリストの内容を確定させる
	HRESULT hr = commandControl.Getter_commandList()->Close();
	assert(SUCCEEDED(hr));

	//GPUにコマンドリストの実行を行わさせる
	ID3D12CommandList* commandLists[] = { commandControl.Getter_commandList() };
	commandControl.Getter_CommandQueue()->ExecuteCommandLists(1, commandLists);
	//GPUとOSに画面の交換を行うように通知する
	swapChainControl.Getter_SwapChain()->Present(1, 0);

	//イベントを待つ
	fenceControl.WaitFenceEvent(commandControl.Getter_CommandQueue(), swapChainControl.Getter_SwapChain());

	fpsController.TimeAdjust();

}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
{
#ifdef USE_IMGUI
	//ImGuiにメッセージを渡す
	if (ImGui_ImplWin32_WndProcHandler(hWnd_, msg_, wParam_, lParam_))
	{
		return true;
	}
#endif

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg_)
	{
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);

		return 0;
	}

	//標準メッセージの処理を行う
	return DefWindowProc(hWnd_, msg_, wParam_, lParam_);

}

void WinApp::TermWnd()
{
	//ウィンドウの登録を解除
	if (m_hInst)
	{
		UnregisterClass(m_windowName, m_hInst);
	}

	m_hInst = nullptr;
	m_hWnd = nullptr;
}

void WinApp::TermD3D()
{
	CloseHandle(fenceControl.Getter_FenceEvent());

#ifdef USE_IMGUI
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif

	CloseWindow(m_hWnd);

	//COMの終了
	CoUninitialize();

}

WinApp::WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_)
	:m_width(width_),
	m_height(height_),
	m_windowName(windowName_),
	m_hInst(nullptr),
	m_hWnd(nullptr)
{
	InitApp();

}

WinApp::~WinApp()
{

}


bool WinApp::InitApp()
{
	// ウィンドウの初期化.
	if (!InitWnd())
	{
		return false;
	}

	// Direct3D 12の初期化.
	if (!InitD3D())
	{
		return false;
	}

	//テクスチャ読み込み含む（コマンド積む）
	M::GetInstance()->Init(&textureDataManager, &exclusiveDraw,
		vpShaders.Getter_VPShaderTable(),&allPipelineSet,&meshCreator,&lightCreator,&cameraParameterSetter);

	commandControl.Getter_commandList()->Close();
	ID3D12CommandList* commandLists[] = { commandControl.Getter_commandList() };
	commandControl.Getter_CommandQueue()->ExecuteCommandLists(1, commandLists);
	fenceControl.WaitFenceEvent(commandControl.Getter_CommandQueue(), swapChainControl.Getter_SwapChain());

	return true;
}

bool WinApp::InitWnd()
{

#ifdef _DEBUG

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}

#endif // _DEBUG


	auto hInst = GetModuleHandle(nullptr);
	if (!hInst)
	{
		return false;
	}

	// ウィンドウクラスの登録
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinApp::WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_windowName;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	//ウィンドウの登録
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	//インスタンスハンドルの設定
	m_hInst = hInst;

	//WindowSize
	RECT rc = {};
	rc.right = static_cast<LONG>(m_width);
	rc.bottom = static_cast<LONG>(m_height);
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);


	// ウィンドウの作成
	m_hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		m_windowName,                   // Window class
		m_windowName,					// Window text
		style,							// Window style
		// Size and position
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,							// Parent window    
		nullptr,							// Menu
		m_hInst,						// Instance handle
		nullptr							// Additional application data
	);

	if (m_hWnd == NULL)
	{
		return false;
	}

	// ウィンドウの表示
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	//ウィンドウにフォーカスを設定
	SetFocus(m_hWnd);


	return true;
}

void WinApp::TermApp()
{
	TermWnd();
	TermD3D();

}









