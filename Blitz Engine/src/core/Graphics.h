#pragma once

#include "core.h"
#include <d3d11.h>

namespace BlitzEngine {

	class BLITZENGINE_API Graphics
	{
	public:
		Graphics() noexcept {};
		bool Init(HWND hwnd);
		void ClearScreen(float red, float green, float blue);
	private:
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTargetView;
	};


}

