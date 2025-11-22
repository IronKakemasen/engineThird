#include "WinApp.h"
#include "./barrierControll/barrierControll.h"
#include <assert.h>
#include "./allPipelineSet/pipelineSet/pipelineCreators/pipelineCreators.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


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
	commandControll.MakeCommandQueue(deviceSetUp.Getter_Device());

	//rtv、srv、dsvそれぞれのdescriptorHeapを作成する
	rtvDescHeap.Init(deviceSetUp.Getter_Device(), 2);
	srvDescHeap.Init(deviceSetUp.Getter_Device(), 64);
	dsvDescriptorHeap.Init(deviceSetUp.Getter_Device(), 1);

	//swapChainの設定
	swapChainControll.Initialize(
		&m_hWnd, commandControll.Getter_CommandQueue(), deviceSetUp.Getter_DxgiFactory(),
		deviceSetUp.Getter_Device(), &rtvDescHeap,&dsvDescriptorHeap);

	//コマンドアローケータの生成
	commandControll.MakeCommandAllocator(deviceSetUp.Getter_Device());

	//コマンドリストの生成
	commandControll.MakeCommandList(deviceSetUp.Getter_Device());

	//fenceControll
	fenceControll.Initialize(deviceSetUp.Getter_Device(), deviceSetUp.Getter_DxgiFactory());

	//pipelineSetの初期化
	allPipelineSet.Initialize(deviceSetUp.Getter_Device(), &vpShaders, commandControll.Getter_commandList());

	//メッシュの初期化、生成
	allMesh.Init(deviceSetUp.Getter_Device());

	//textureDataManagerの初期化
	textureDataManager.Init(&srvDescHeap,deviceSetUp.Getter_Device(), commandControll.Getter_commandList());


	auto inputLayOutFunc = []() 
		{
		std::vector<D3D12_INPUT_ELEMENT_DESC> descs;
		descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		));

		descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		));

		descs.emplace_back(InputLayoutDescCreator::GetInputElementDesc(
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			D3D12_APPEND_ALIGNED_ELEMENT
		));

		return descs;

	};

	auto rootparameterFunc = []() {

		std::vector<D3D12_ROOT_PARAMETER> meters;

		meters.emplace_back(RootSignatureCreator::GetRootParameterWithDescriptorRange(
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			D3D12_SHADER_VISIBILITY_PIXEL,
			0));

		meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(0));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(1));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterVertexShader(2));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(3));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(4));

		return meters;
	};

	allPipelineSet.CreateNewPipeline("Object3d.VS", "Object3d.PS", inputLayOutFunc, rootparameterFunc);


#ifdef USE_IMGUI
	//ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX12_Init(
		deviceSetUp.Getter_Device(),
		swapChainControll.Ref_SwapChainDesc().BufferCount,
		swapChainControll.Ref_RenderTargetDesc().Format,
		srvDescHeap.Getter_Descriptorheap(),
		srvDescHeap.Getter_Descriptorheap()->GetCPUDescriptorHandleForHeapStart(),		//SRVHeap上の０番目
		srvDescHeap.Getter_Descriptorheap()->GetGPUDescriptorHandleForHeapStart());
#endif

	commandControll.Getter_commandList()->Close();
	return true;
}

void WinApp::BeginFrame()
{
	//描画先のRTV、DSVを設定する
	//swapChainControll.Getter_DepthBuffer() = descriptorHeapSet.dH_dsv->GetCPUDescriptorHandleForHeapStart();

	//Imguiにここからフレームが始まる旨を告げる
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// コマンドの記録を開始.
	commandControll.PrepareForNextCommandList();

	//バリア
	D3D12_RESOURCE_BARRIER barrier = BarrierControll::Create(
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Resource(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

	//TransitionBarrierを張る
	BarrierControll::Pitch(&commandControll, &barrier);

	// レンダーゲットの設定.
	commandControll.Getter_commandList()->OMSetRenderTargets(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Handle(), false,
		swapChainControll.Getter_DepthBuffer()->Getter_Handle());
	//commandControll.Getter_commandList()->OMSetRenderTargets(1,
	//	swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Handle(), FALSE, nullptr);

	
	//指定した深度で画面クリアする
	commandControll.Getter_commandList()->ClearDepthStencilView(*swapChainControll.Getter_DepthBuffer()->Getter_Handle(),
		D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//指定した色で画面全体をクリアする
	commandControll.Getter_commandList()->ClearRenderTargetView(
		*swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Handle(), windowColor, 0, nullptr);

	////描画用のDescriptorHeapの設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescHeap.Getter_Descriptorheap()};
	commandControll.Getter_commandList()->SetDescriptorHeaps(1, descriptorHeaps);

	//DXの行列の設定
	commandControll.Getter_commandList()->RSSetViewports(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_ViewportMatrix());

	commandControll.Getter_commandList()->RSSetScissorRects(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->ScissorRect());


}

void WinApp::EndFrame()
{
	//[ 画面に書く処理が終わり、画面に映すので状態を遷移 ]
	ImGui::Render();
	//実際のcommandListのImguiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandControll.Getter_commandList());

	//バリア
	//RenderTarget->Prsent
	D3D12_RESOURCE_BARRIER barrier = BarrierControll::Create(
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Resource(),
		D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		D3D12_RESOURCE_BARRIER_FLAG_NONE,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

	//TransitionBarrierを張る
	BarrierControll::Pitch(&commandControll, &barrier);

	//コマンドリストの内容を確定させる
	HRESULT hr = commandControll.Getter_commandList()->Close();
	assert(SUCCEEDED(hr));

	//GPUにコマンドリストの実行を行わさせる
	ID3D12CommandList* commandLists[] = { commandControll.Getter_commandList() };
	commandControll.Getter_CommandQueue()->ExecuteCommandLists(1, commandLists);
	//GPUとOSに画面の交換を行うように通知する
	swapChainControll.Getter_SwapChain()->Present(1, 0);

	//イベントを待つ
	fenceControll.WaitFenceEvent(commandControll.Getter_CommandQueue(), swapChainControll.Getter_SwapChain());


}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
{
	//ImGuiにメッセージを渡す
	if (ImGui_ImplWin32_WndProcHandler(hWnd_, msg_, wParam_, lParam_))
	{
		return true;
	}

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
	CloseHandle(fenceControll.Getter_FenceEvent());


	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


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









