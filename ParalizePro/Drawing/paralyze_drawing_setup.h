#pragma once
#include <Windows.h>
#include <wrl.h>
#include <dxgi.h>
#include <d2d1.h>
#include <d3d11.h>
#include <d2d1_2.h>
#include <dcomp.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dcomp.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")

class temporary_window
{
	constexpr static auto WindowClassName = "AppWindowClass";
	constexpr static auto WindowTitle = "";

	HWND window;
public:
	temporary_window()
	{
		WNDCLASS wc{};

		wc.lpszClassName = L"AppWindowClass";
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpfnWndProc = [](const HWND window, const UINT message, const WPARAM wparam, const LPARAM lparam) -> LRESULT
		{
			return DefWindowProc(window, message, wparam, lparam);
		};

		RegisterClass(&wc);

		this->window = CreateWindowA(WindowClassName, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
	}

	~temporary_window()
	{
		if (this->window)
			DestroyWindow(this->window);

		UnregisterClassA(WindowClassName, GetModuleHandle(nullptr));
	}

	void destroy() const
	{
		if (this->window)
			DestroyWindow(this->window);

		UnregisterClassA(WindowClassName, GetModuleHandle(nullptr));
	}

	HWND handle() const
	{
		return window;
	}
};


namespace swapchain_creator {
	extern bool build_composition(HWND hWindow);
	extern void clean_target();
	extern void init_rendering(HWND gameWindow);
	extern void cleanup_device_d3d();
	extern HRESULT create_device_d3d(HWND hWnd);
};

