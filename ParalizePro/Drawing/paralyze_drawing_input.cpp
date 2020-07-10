#include "paralyze_drawing_input.h"
#include "../CheatManager.h"
#include "../ImGui/imgui.h"
#include <thread>


paralyze_drawing_input::paralyze_drawing_input()
{
}


paralyze_drawing_input::~paralyze_drawing_input()
{
}


void mouse_handler_thread()
{
	while (true)
	{
		POINT mousePosition;
		GetCursorPos(&mousePosition);
		ScreenToClient(pcd->game_window, &mousePosition);//resolve mouse click to window size shit

		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = mousePosition.x;
		io.MousePos.y = mousePosition.y;


		if (GetAsyncKeyState(VK_LBUTTON)) {
			//io.MouseClicked[0] = true;
			io.MouseDown[0] = true;
		}
		else {
			io.MouseDown[0] = false;
			//io.MouseClicked[0] = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}
}

void keyboard_handler_thread()
{
	while (true)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (GetAsyncKeyState(VK_RETURN))
		{

			std::cout << sizeof(io.InputQueueCharacters) << std::endl;

			Sleep(100);
		}
		//else
		//{
		//	io.KeysDown[ImGuiKey_Enter] = 0;
		//	//Sleep(100);
		//}
		if (GetAsyncKeyState(VK_BACK) < 0)
		{
			io.KeysDown[VK_BACK] = 1;
			Sleep(10);
		}
		else
		{
			io.KeysDown[VK_BACK] = 0;
			Sleep(10);
		}

		if (io.WantCaptureKeyboard)
		{
			GetKeyState(0);
			BYTE arr[256];
			if (GetKeyboardState(arr));
			{
				for (int i = 0; i < sizeof(arr); ++i)
				{
					if ((GetKeyState(i) & 0x00000080) && (io.WantCaptureHotkey ? true : (i != VK_BACK && i != VK_RETURN && i != VK_LBUTTON && i != VK_RBUTTON && i != VK_SHIFT && i != VK_CAPITAL)))
					{
						int lol = (int)arr[i];
						if (io.WantCaptureHotkey || !io.MouseDown[0]) {
							WORD p;
							ToAscii(i, ::MapVirtualKey(i, MAPVK_VK_TO_VSC), &arr[0], &p, 0);
							std::cout << (int)i << " " << (char)p << std::endl;
							io.AddInputCharacter((unsigned int)(char)p);
							io.KeysDown[i] = 1;
							Sleep(50);
						}
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 20));
	}
}

void paralyze_drawing_input::spinup_threads()
{
	std::thread mouse_thread(mouse_handler_thread);
	mouse_thread.detach();

	std::thread keyboard_thread(keyboard_handler_thread);
	keyboard_thread.detach();
}
