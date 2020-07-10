#pragma once
#include "paralyze_drawing_setup.h"
#include "paralyze_drawing_input.h"
#include "paralyze_drawing_menu.h"
#include "paralyze_drawing_visuals.h"

class paralyze_drawing
{
public:
	paralyze_drawing();
	~paralyze_drawing();

	void start_drawing();
	void init_drawing(HWND gameWindow);

	
	paralyze_drawing_input* pcdi;
	paralyze_drawing_menu* pcdm;
	paralyze_drawing_visuals* pcdv;

	HWND game_window = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
	ID3D11Device*            g_pd3dDevice = nullptr;
	IDXGIDevice*                    g_dxgiDevice = nullptr;
	ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
	IDXGISwapChain1*          g_pSwapChain = nullptr;
	ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;
	IDXGIFactory2*           dxgiFactory = nullptr;

	IDCompositionDevice* compositionDevice = nullptr;
	IDCompositionTarget* compositionTarget = nullptr;
	IDCompositionVisual* compositionVisual = nullptr;
};

