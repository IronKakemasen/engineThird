#include "fenceControll.h"
#include <assert.h>
#include "../WinApp.h"


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

void FenceControll::WaitFenceEvent(ID3D12CommandQueue* commandQueue_, IDXGISwapChain4* swapChain_)
{
	////Fenceの値を更新
	//fenceCounter[SwapChainControll::frameIndex]++;
	
	//GPUがここまでたどり着いたとき、
	//fenceの値を指定した値に代入するようにSignalを送る
	const auto currentValue = fenceCounter[SwapChainControll::frameIndex];

	commandQueue_->Signal(fence.Get(), currentValue);

	// バックバッファ番号を更新.
	SwapChainControll::frameIndex = swapChain_->GetCurrentBackBufferIndex();


	//fenceの値が指定したSignal値にたどり着いているか確認する
	//GetCompletedValueの初期値はfence作成時に渡した初期値
	if (fence->GetCompletedValue() < fenceCounter[SwapChainControll::frameIndex])
	{
		//指定したSignalにたどり着いていないので、たどり着くまで待つ
		fence->SetEventOnCompletion(fenceCounter[SwapChainControll::frameIndex], fenceEvent);
		//イベント待つ
		WaitForSingleObjectEx(fenceEvent, INFINITE,FALSE);
	}

	// 次のフレームのフェンスカウンターを増やす.
	fenceCounter[SwapChainControll::frameIndex] = currentValue + 1;

}


void FenceControll::Initialize(ID3D12Device* device_, IDXGIFactory7* dxgiFactory_)
{
	SetFence(device_, dxgiFactory_);
}

void FenceControll::SetFence(ID3D12Device* device_, IDXGIFactory7* dxgiFactory_)
{
	//HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));

	HRESULT hr = device_->CreateFence(
		fenceCounter[SwapChainControll::frameIndex],
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(fence.GetAddressOf()));

	assert(SUCCEEDED(hr));
	Log(WinApp::log, "Complete built fence\n");

	fenceCounter[SwapChainControll::frameIndex]++;

	//FenceのSignalを待つためのイベント（WINDOWへのメッセージ）を作成する
	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent != nullptr);
	Log(WinApp::log, "Complete creat event\n");

}
