#pragma once

#include "../gpuResources/ColorBuffer/ColorBuffer.h"
#include <dxgi1_6.h>



class SwapChainControll
{
public:

	static inline const UINT kFrameBufferCnt  = 2;
	static inline UINT frameIndex = 0;


private:

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
	ColorBuffer colorBuffers[kFrameBufferCnt];

	void CreateRenderTargetView(ID3D12Device* device_, RtvDescriptorHeap* rtvDescHeap_);

	//swapChainの生成
	DXGI_SWAP_CHAIN_DESC1 CreateSwapChain(HWND* hwnd_, ID3D12CommandQueue* commandQueue_,
		IDXGIFactory7* dxgiFactory_);

	//SwapChainからリソースを引っ張る
	void PullSwapChainResource();


public:

	inline auto* Getter_SwapChain()
	{
		return swapChain.Get();
	}

	inline auto* Getter_ColorBuffer(uint8_t index_)
	{
		return &colorBuffers[index_];
	}



	DXGI_SWAP_CHAIN_DESC1 Initialize(HWND* hwnd_, ID3D12CommandQueue* commandQueue_,
		IDXGIFactory7* dxgiFactory_, ID3D12Device* device_, RtvDescriptorHeap* rtvDescHeap_);


};


