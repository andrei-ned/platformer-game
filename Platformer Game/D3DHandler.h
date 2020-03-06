#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "DirectXColors.h"
#include "WinData.h"

class D3DHandler
{
public:
	D3DHandler(WinData winData);
	~D3DHandler();
	//default minimum behaviour when ALT+ENTER or drag or resize
	//parameters are new width and height of window
	void OnResize(int clientWidth, int clientHeight);
	void BeginRender(const DirectX::SimpleMath::Color color = DirectX::Colors::Black.v);
	void EndRender();
	ID3D11Device& GetDevice();
	ID3D11DeviceContext& GetDeviceCtx();
	bool GetDeviceReady() const;
	ID3D11SamplerState& GetWrapSampler();
	D3D11_VIEWPORT& GetScreenViewport();
private:
	//what type of gpu have we got - hopefully a hardware one
	D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_UNKNOWN;
	//texture multisampling quality level supported
	UINT m4xMsaaQuality = 0;
	//depth buffer for sorting pixels by distance from camera
	ID3D11Texture2D* mpDepthStencilBuffer = nullptr;
	bool mEnable4xMsaa = true;
	//running in a window?
	bool mWindowed = false;
	//main handle used to create resources and access D3D
	ID3D11Device* mpd3dDevice = nullptr;
	//a handle off the device we can use to give rendering commands
	ID3D11DeviceContext* mpd3dImmediateContext = nullptr;
	//a number of surfaces we can render onto and then display
	IDXGISwapChain* mpSwapChain = nullptr;
	//when we render things, where do the go?
	ID3D11RenderTargetView* mpRenderTargetView = nullptr;
	//when rendering we can test the depth of pixels, usually so we
	//avoid rendering anything that is behind something else
	ID3D11DepthStencilView* mpDepthStencilView = nullptr;
	//position, height, width, min+max depth of the view we are rendering
	D3D11_VIEWPORT mScreenViewport;

	ID3D11SamplerState* mpWrapSampler = nullptr;

	//heavy lifting to start D3D11
	void CreateD3D(D3D_FEATURE_LEVEL desiredFeatureLevel = D3D_FEATURE_LEVEL_11_0);
	//buffers in the swap chain must match the screen resolution
	void ResizeSwapChain(int screenWidth, int screenHeight);
	//the kind of depth stencil we want
	void CreateDepthStencilDescription(D3D11_TEXTURE2D_DESC& dsd, int screenWidth, int screenHeight, bool msaa4X, int maxQuality);
	//create all render buffers
	void CreateDepthStencilBufferAndView(D3D11_TEXTURE2D_DESC& dsd);
	// Bind the render target view and depth/stencil view to the pipeline.
	void BindRenderTargetViewAndDepthStencilView();
	//viewport dimensions need updating when the window changes size
	void SetViewportDimensions(int screenWidth, int screenHeight);
	//can this gpu support 4x sampling
	void CheckMultiSamplingSupport(UINT& quality4xMsaa);
	//specify the type of swapchain needed
	void CreateSwapChainDescription(DXGI_SWAP_CHAIN_DESC& sd, HWND hMainWnd, bool windowed, int screenWidth, int screenHeight);
	//once you have a description you can create the swapchain needed
	void CreateSwapChain(DXGI_SWAP_CHAIN_DESC& sd);

	void CreateWrapSampler(ID3D11SamplerState* &pSampler);
};

