#include "commandControll.h"
#include <assert.h>
#include "../swapChainControll/swapChainControll.h"
#include "../WinApp.h"

#pragma comment(lib,"d3d12.lib")

void CommandControll::PrepareForNextCommandList()
{

	HRESULT hr = commandAllocators[SwapChainControll::frameIndex]->Reset();
	assert(SUCCEEDED(hr));

	hr = commandList->Reset(commandAllocators[SwapChainControll::frameIndex].Get(), nullptr);
	assert(SUCCEEDED(hr));

}


void CommandControll::MakeCommandQueue(ID3D12Device* device_)
{
	D3D12_COMMAND_QUEUE_DESC desc{};

	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;


	HRESULT hr = device_->CreateCommandQueue(&desc,
		IID_PPV_ARGS(commandQueue.GetAddressOf()));

	//コマンドキューの生成がうまくいかなかった場合はエラー
	assert(SUCCEEDED(hr));
	Log(WinApp::log, "Complete create CommandQueue\n");
}
void CommandControll::MakeCommandAllocator(ID3D12Device* device_)
{
	commandAllocators.resize(SwapChainControll::kFrameBufferCnt );

	for (int i = 0; i < SwapChainControll::kFrameBufferCnt ; ++i)
	{
		
		HRESULT hr = device_->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(commandAllocators[i].GetAddressOf()));

		//生成がうまくいかなかった場合はエラー
		assert(SUCCEEDED(hr));

	}

	Log(WinApp::log, "Complete create Allocators\n");
}
void CommandControll::MakeCommandList(ID3D12Device* device_)
{
	HRESULT hr = device_->CreateCommandList(0, 
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocators[SwapChainControll::frameIndex].Get(),
		nullptr, 
		IID_PPV_ARGS(commandList.GetAddressOf()));

	//生成失敗
	assert(SUCCEEDED(hr));
	Log(WinApp::log, "Complete create CommandList\n");
}
