#include "paralyze_drawing_setup.h"
#include "../CheatManager.h"
#include <ThemidaSDK.h>
#include "Renderer.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
#include <Windows.h>
#include <WinUser.h>
#include "../MetaStr.h"

namespace swapchain_creator {
	bool build_composition(HWND hWindow)
	{
		VM_TIGER_BLACK_START
			STR_ENCRYPT_START


			if (!hWindow) {
				MessageBoxA(0, METASTRING("Window is invalid. Did the driver load?"), "", 0);
			}
		HRESULT result = DCompositionCreateDevice(pcd->g_dxgiDevice, __uuidof(pcd->compositionDevice), reinterpret_cast<void**>(&pcd->compositionDevice));
		if (FAILED(result))
		{
			MessageBoxA(0, METASTRING("[!] DCompositionCreateDevice failed."), "", 0);;
			return false;
		}

		result = pcd->compositionDevice->CreateTargetForHwnd(hWindow, true, &pcd->compositionTarget);
		if (FAILED(result))
		{
			MessageBoxA(0, METASTRING("[!] CreateTargetForHwnd( ) failed."), "", 0);;
			if (result == DCOMPOSITION_ERROR_WINDOW_ALREADY_COMPOSED)
			{
				MessageBoxA(0, METASTRING("[!] You have already injected once. (DCOMPOSITION_ERROR_WINDOW_ALREADY_COMPOSED)"), "", 0);;
				printf(METASTRING("[!] DCOMPOSITION_ERROR_WINDOW_ALREADY_COMPOSED\n"));
			}
			return false;
		}

		result = pcd->compositionDevice->CreateVisual(&pcd->compositionVisual); if (FAILED(result)) { MessageBoxA(0, METASTRING("[!] CreateVisual failed."), "", 0);; };
		result = pcd->compositionVisual->SetContent(pcd->g_pSwapChain); if (FAILED(result)) { MessageBoxA(0, METASTRING("[!] SetContent failed."), "", 0);; };
		result = pcd->compositionTarget->SetRoot(pcd->compositionVisual); if (FAILED(result)) { MessageBoxA(0, METASTRING("[!] SetRoot failed."), "", 0);; };
		result = pcd->compositionDevice->Commit(); if (FAILED(result)) { MessageBoxA(0, METASTRING("[!] Commit failed."), "", 0);; };
		result = pcd->compositionDevice->WaitForCommitCompletion(); if (FAILED(result)) { MessageBoxA(0, METASTRING("[!] WaitForCommitCompletion failed."), "", 0); };
		STR_ENCRYPT_END
			VM_TIGER_BLACK_END
			return true;
	}
	void create_render_target()
	{
		DXGI_SWAP_CHAIN_DESC sd;
		pcd->g_pSwapChain->GetDesc(&sd);

		ID3D11Texture2D* pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
		ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
		render_target_view_desc.Format = sd.BufferDesc.Format;
		render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		pcd->g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pcd->g_pd3dDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &pcd->g_mainRenderTargetView);
		pcd->g_pd3dDeviceContext->OMSetRenderTargets(1, &pcd->g_mainRenderTargetView, NULL);
		pBackBuffer->Release();
	}
	HRESULT create_device_d3d(HWND hWnd)
	{
		VM_TIGER_BLACK_START
			STR_ENCRYPT_START
		RECT window_rect;

		if (!GetClientRect(hWnd, &window_rect))
		{
			MessageBoxA(0, METASTRING("[!] Invalid window\n"), "", 0);;
			return false;
		}

		HRESULT result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, &pcd->g_pd3dDevice, nullptr, &pcd->g_pd3dDeviceContext);
		pcd->g_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pcd->g_dxgiDevice));
		result = CreateDXGIFactory2(NULL, __uuidof(pcd->dxgiFactory), reinterpret_cast<void**>(&pcd->dxgiFactory));

		DXGI_SWAP_CHAIN_DESC1 description = { };
		description.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		description.BufferCount = 2;
		description.SampleDesc.Count = 1;
		description.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

		description.Width = pcd->screenWidth = window_rect.right - window_rect.left;
		description.Height = pcd->screenHeight = window_rect.bottom - window_rect.top;

		Global::monitorX = description.Width;
		Global::monitorY = description.Height;

		pcd->dxgiFactory->CreateSwapChainForComposition(pcd->g_pd3dDevice, &description, nullptr, &pcd->g_pSwapChain);

		create_render_target();

		STR_ENCRYPT_END
			VM_TIGER_BLACK_END
		return S_OK;
	}

	void init_rendering(HWND gameWindow)
	{
		VM_TIGER_BLACK_START
			STR_ENCRYPT_START
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(gameWindow);
		ImGui_ImplDX11_Init(pcd->g_pd3dDevice, pcd->g_pd3dDeviceContext);

		Renderer::GetInstance()->Initialize();

		temporary_window window;
		uint64_t WndThreadInfoLocal = pcm->get_wnd_thread(window.handle());
		uint64_t WndThreadInfoTarget = pcm->get_wnd_thread(gameWindow);
		//printf("[+] kernel pointers\n");
		//printf("     local: %llx\n", WndThreadInfoLocal);
		//printf("     target:%llx\n", WndThreadInfoTarget);

		pcm->set_wnd_thread(gameWindow, WndThreadInfoLocal);
		if (swapchain_creator::build_composition(gameWindow))
			Sleep(1);
		else
			MessageBoxA(0, METASTRING("[!] Composition has been destroyed too early."), "", 0);;

		pcm->set_wnd_thread(gameWindow, WndThreadInfoTarget);

		window.destroy();
		STR_ENCRYPT_END
		VM_TIGER_BLACK_END
	}

	void cleanup_render_target()
	{
		if (pcd->g_mainRenderTargetView) { pcd->g_mainRenderTargetView->Release(); pcd->g_mainRenderTargetView = NULL; }
	}
	void cleanup_device_d3d()
	{
		cleanup_render_target();
		if (pcd->g_pSwapChain) { pcd->g_pSwapChain->Release(); pcd->g_pSwapChain = NULL; }
		if (pcd->g_pd3dDeviceContext) { pcd->g_pd3dDeviceContext->Release(); pcd->g_pd3dDeviceContext = NULL; }
		if (pcd->g_pd3dDevice) { pcd->g_pd3dDevice->Release(); pcd->g_pd3dDevice = NULL; }
	}
}
