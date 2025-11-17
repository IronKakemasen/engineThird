#include "WinApp.h"
#include "./barrierControll/barrierControll.h"
#include <assert.h>
#include "./allPipelineSet/pipelineSet/pipelineCreators/pipelineCreators.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


bool WinApp::InitD3D()
{
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
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = swapChainControll.Initialize(
		&m_hWnd, commandControll.Getter_CommandQueue(), deviceSetUp.Getter_DxgiFactory(),
		deviceSetUp.Getter_Device(), &rtvDescHeap);

	//コマンドアローケータの生成
	commandControll.MakeCommandAllocator(deviceSetUp.Getter_Device());

	//コマンドリストの生成
	commandControll.MakeCommandList(deviceSetUp.Getter_Device());

	//fenceControll
	fenceControll.Initialize(deviceSetUp.Getter_Device(), deviceSetUp.Getter_DxgiFactory());

	//pipelineSetの初期化
	allPipelineSet.Initialize(deviceSetUp.Getter_Device(), &vpShaders, commandControll.Getter_commandList());

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
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(2));
		meters.emplace_back(RootSignatureCreator::GetRootParaMeterPixelShader(3));

		return meters;
	};

	allPipelineSet.CreateNewPipeline("Object3d.VS", "Object3d.PS", inputLayOutFunc, rootparameterFunc);

	//vpShaders.AddPixelShader("Object3d.PS");
	//vpShaders.AddVertexShader("Object3d.VS");
	//vpShaders.AddToTable("Default,Default", "Object3d.PS", "Object3d.VS");
	//allPipelineSet.Add("Default,Default");

	commandControll.Getter_commandList()->Close();

	//
	//if (shaderSetName_ == "Object3d.VSObject3d.PS")
	//{
	//	numRootParameters = 5;
	//
	//	heap_rootParameters = new D3D12_ROOT_PARAMETER[numRootParameters];
	//
	//	//Descriptortableを使う
	//	heap_rootParameters[0] = GetRootParaMeterDescriptorRange();
	//	//WorldMatrix
	//	heap_rootParameters[1] = GetRootParaMeterVertexShader(0);
	//	//CameraPara
	//	heap_rootParameters[2] = GetRootParaMeterVertexShader(1);
	//
	//	//Material
	//	heap_rootParameters[3] = GetRootParaMeterPixelShader(2);
	//	//DirectionalLight
	//	heap_rootParameters[4] = GetRootParaMeterPixelShader(3);
	//}

	return true;
}

void WinApp::TermApp()
{
	TermWnd();
	TermD3D();
}


LRESULT CALLBACK WinApp::WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_)
{
	////ImGuiにメッセージを渡す
	//if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	//{
	//	return true;
	//}

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



WinApp::WinApp(uint32_t width_, uint32_t height_,LPCWSTR windowName_)
	:m_width(width_),
	m_height(height_),
	m_windowName(windowName_),
	m_hInst(nullptr),
	m_hWnd(nullptr)
{
	InitApp();

}

WinApp::~WinApp()
{ }


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

	CloseWindow(m_hWnd);

}

void WinApp::BeginFrame()
{
	//描画先のRTV、DSVを設定する
	//depthStencilSetUp.dsvHandle = descriptorHeapSet.dH_dsv->GetCPUDescriptorHandleForHeapStart();

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

	//commandControll.commandList->OMSetRenderTargets(1,
	//	&swapChainControll.swapChain_resourcesAndHandles[backBufferIndex].rtvHandle, false, &depthStencilSetUp.dsvHandle);
	// レンダーゲットの設定.
	commandControll.Getter_commandList()->OMSetRenderTargets(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Handle(), FALSE, nullptr);


	//指定した深度で画面クリアする
	//commandControll.commandList->ClearDepthStencilView(depthStencilSetUp.dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//指定した色で画面全体をクリアする
	commandControll.Getter_commandList()->ClearRenderTargetView(
		*swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_Handle(), windowColor, 0, nullptr);

	//////描画用のDescriptorHeapの設定
	//ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeapSet.dH_srv.Get() };
	//commandControll.commandList->SetDescriptorHeaps(1, descriptorHeaps);

	//DXの行列の設定
	commandControll.Getter_commandList()->RSSetViewports(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->Getter_ViewportMatrix());

	commandControll.Getter_commandList()->RSSetScissorRects(1,
		swapChainControll.Getter_ColorBuffer(swapChainControll.frameIndex)->ScissorRect());

}

void WinApp::EndFrame()
{
	//[ 画面に書く処理が終わり、画面に映すので状態を遷移 ]

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
	BarrierControll::Pitch(&commandControll,&barrier);

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












