#include "swapChainControll.h"
#include <assert.h>
#include "../WinApp.h"
#include "../../../commonVariables.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

void SwapChainControll::CreateDepthSencilView(ID3D12Device* device_, DsvDescriptorHeap* dsvDescHeap_)
{
	depthBuffer.CreateDepthStencilTextureResource(device_, (int)V_Common::kWindow_W, (int)V_Common::kWindow_H);
	auto desc = depthBuffer.CreateDepthStencilViewDesc();
	depthBuffer.CreateDSV(device_, dsvDescHeap_, desc);
}

void SwapChainControll::CreateRenderTargetView(ID3D12Device* device_, RtvDescriptorHeap* rtvDescHeap_)
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = colorBuffers->CreateRTV_Desc();

	for (int i = 0u; i < kFrameBufferCnt; ++i)
	{
		colorBuffers[i].CreateRTV(device_, rtvDescHeap_, rtvDesc);
	}

	renderTargetDescForImGui = rtvDesc;
}


//swapChainの生成
DXGI_SWAP_CHAIN_DESC1 SwapChainControll::CreateSwapChain(HWND* hwnd_, ID3D12CommandQueue* commandQueue_,
	IDXGIFactory7* dxgiFactory_)
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//画面の縦横。クライアント領域と同じにしておく
	swapChainDesc.Width = (UINT)V_Common::kWindow_W;
	swapChainDesc.Height = (UINT)V_Common::kWindow_H;
	//色の形成
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//マルチサンプルしない
	swapChainDesc.SampleDesc.Count = 1;
	//描画のターゲットとして利用する
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//ダブルバッファ
	swapChainDesc.BufferCount = 2;
	//モニタに移したら中身を破棄
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	HRESULT hr = dxgiFactory_->CreateSwapChainForHwnd(commandQueue_, *hwnd_, &swapChainDesc,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain.GetAddressOf()));
	//生成失敗
	assert(SUCCEEDED(hr));
	Log(WinApp::log, "Complete create SwapChain\n");

	//バックバッファ番号を取得
	frameIndex = swapChain.Get()->GetCurrentBackBufferIndex();

	return swapChainDesc;
}

//SwapChainからリソースを引っ張る
void SwapChainControll::PullSwapChainResource()
{
	Log(WinApp::log, "Complete create rtvDescriptorHeap\n");

	//SwapChainからResourceを引っ張ってくる
	HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(colorBuffers[0].Getter_ResourcePP()));
	//生成失敗
	assert(SUCCEEDED(hr));
	hr = swapChain->GetBuffer(1, IID_PPV_ARGS(colorBuffers[1].Getter_ResourcePP()));
	//生成失敗
	assert(SUCCEEDED(hr));
	Log(WinApp::log, "Complete pull Resource\n");

}

void SwapChainControll::Initialize(HWND* hwnd_, ID3D12CommandQueue* commandQueue_,
	IDXGIFactory7* dxgiFactory_, ID3D12Device* device_, 
	RtvDescriptorHeap* rtvDescHeap_, DsvDescriptorHeap* dsvDescHeap_)
{
	swapChainDescForImGui = CreateSwapChain(hwnd_, commandQueue_, dxgiFactory_);

	PullSwapChainResource();

	CreateRenderTargetView(device_, rtvDescHeap_);
	CreateDepthSencilView(device_, dsvDescHeap_);

	for (int i = 0u; i < kFrameBufferCnt; ++i)
	{
		colorBuffers[i].SetDXMatrix(V_Common::kWindow_W, V_Common::kWindow_H);
	}

}
