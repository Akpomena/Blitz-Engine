#pragma once

#include "core.h"
#include <d3d11.h>
#include <wrl.h>

namespace BlitzEngine {

	class BLITZENGINE_API Graphics
	{
	public:
		Graphics() noexcept {};
		bool Init(HWND hwnd);
		void ClearScreen(float red, float green, float blue) noexcept;
		void DrawTriangle();
	private:
		HWND m_Hwnd;	
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
	};


}

