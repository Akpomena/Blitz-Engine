#pragma once
#include "../core/Core.h"
#include <d3d11.h>
#include <wrl.h>

namespace BlitzEngine {

	class BLITZENGINE_API Renderer
	{
	public:
		static bool Init(HWND hwnd, float width, float height);
		static void ShutDown() noexcept;
		static void ClearScreen(float red, float green, float blue) noexcept;
		static void SetViewPort(float width, float height);
		static void Present() noexcept;

		inline static bool IsInitialized() { return m_Initialized; }
	public:
		static bool m_Initialized;
		static HWND m_Hwnd;
		static Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		static Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		static Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		static Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
	};

}