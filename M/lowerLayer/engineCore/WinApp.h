#pragma once

#include "../../commonVariables.h"

//=================================================================== debugSystems
#include "./logAndException/outputDebugLog.h"
#include "./logAndException/detectException.h"
//===================================================================

//=================================================================== descriptorHeaps
#include "./allDescriptorHeap/rtvDescriptorHeap/rtvDescriptorHeap.h"
#include "./allDescriptorHeap/dsvDescriptorHeap/dsvDescriptorHeap.h"		
#include "./allDescriptorHeap/srvDescriptorHeap/srvDescriptorHeap.h"
//===================================================================

//=================================================================== otherCoreSystems
#include "./deviceSetUp/deviceSetUp.h"
#include "./fenceControll/fenceControll.h"
#include "./commandControll/commandControll.h"
#include "./swapChainControll/swapChainControll.h"
#include "./dxCompile/dxCompile.h"
//===================================================================

//=================================================================== shaderData,Table
#include "./allShaderData/vpShaders.h"
//===================================================================

//=================================================================== allPipelineSet
#include "./allPipelineSet/allPipelineSet.h"
//===================================================================

//=================================================================== Imgui
#ifdef USE_IMGUI
#include "../../../External/imgui/imgui.h"
#include "../../../External/imgui/imgui_impl_dx12.h"
#include "../../../External/imgui/imgui_impl_win32.h"
#endif 
////===================================================================

//#include "../../../External/DirectXTex/d3dx12.h"



class WinApp
{
public:

	static inline std::ofstream log;


	WinApp(uint32_t width_, uint32_t height_, LPCWSTR windowName_);
	void TermApp();
	void BeginFrame();
	void EndFrame();

	~WinApp();

private:

	float windowColor[4] = { 0.1f,0.1f,0.1f,1.0f };

#ifdef _DEBUG
	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController = nullptr;
#endif 


	HINSTANCE m_hInst;
	HWND m_hWnd;
	uint32_t m_width;
	uint32_t m_height;
	LPCWSTR m_windowName;


	//[ DeviceSetUp ]
	DeviceSetUp deviceSetUp;

	//[ CommandControll ]
	CommandControll commandControll;

	//[ FenceControll ]
	FenceControll fenceControll;

	//[ SwapChain ]
	SwapChainControll swapChainControll;

	//[ DxCompile ]
	DxCompile dxCompile;

	//[ DescriptorHeaps ]
	RtvDescriptorHeap rtvDescHeap;
	SrvDescriptorHeap srvDescHeap;
	DsvDescriptorHeap dsvDescriptorHeap;

	//[ ShaderData , vpShadertable  ]
	VpShaders vpShaders;

	//[ AllPipelineSet ]
	AllPipelineSet allPipelineSet;

	bool InitApp();
	bool InitWnd();
	void TermWnd();

	bool InitD3D();
	void TermD3D();


	static LRESULT CALLBACK WndProc(HWND hWnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);



};

template<typename T>
void SafeRelease(T*& ptr)
{
	if (ptr != nullptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}

