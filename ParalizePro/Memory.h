#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <apiquery2.h>
#include <consoleapi2.h>
#include <processthreadsapi.h>
#include <libloaderapi.h>

class ParalyzeCheatMemory
{
public:
		typedef struct _HOOK_READ_REQUEST
		{
			ULONG ProcessId;

			ULONGLONG Address;
			void *Response;
			ULONGLONG Size;
		} HOOK_READ_REQUEST, *PHOOK_READ_REQUEST;

		typedef struct _HOOK_WRITE_REQUEST
		{
			ULONG ProcessId;

			UINT_PTR Value;
			UINT_PTR Address;
			ULONG Size;

		} HOOK_WRITE_REQUEST, *PHOOK_WRITE_REQUEST;

		typedef struct _HOOK_RENDERER_REQUEST
		{
			UINT_PTR hwnd;
			UINT_PTR lpThreadInfo;
			ULONG     UserPID;
			ULONGLONG UserBufferAdress;
		} HOOK_RENDERER_REQUEST, *PHOOK_RENDERER_REQUEST;

		enum PROTO_MESSAGE {
			PROTO_GET_BASEADDR = 0,
			PROTO_NORMAL_READ = 1,
			PROTO_NORMAL_WRITE = 2,
			PROTO_RENDERER_GET_WND_THREAD = 3,
			PROTO_RENDERER_SET_WND_THREAD = 4,
			PROTO_UNHOOK = 5
		};


		typedef struct _HOOK_BASE_REQUEST
		{
			ULONGLONG UserBufferAdress;
			ULONGLONG ReadSize;
			ULONG     UserPID;
			ULONG     GamePID;
		} HOOK_BASE_REQUEST, *PHOOK_BASE_REQUEST;


		 FARPROC fnNtQueryIntervalProfile = GetProcAddress(LoadLibraryA("gdi32full.dll"), "NtGdiDdDDINetDispStopMiracastDisplayDevice");
		 typedef HRESULT(__stdcall *tNtQueryIntervalProfile)(UINT_PTR test, HANDLE test2);
		 tNtQueryIntervalProfile NtGdiDdDDINetDispStopMiracastDisplayDevice = reinterpret_cast<tNtQueryIntervalProfile>(fnNtQueryIntervalProfile);

		 DWORD r6pid;
		 uint64_t r6base;
		 std::string cheat_username;

		int64_t getbase()
		{
			int64_t base = 0;
			HOOK_BASE_REQUEST hook_base_request{ (uint64_t)&base, sizeof(int64_t), (uint32_t)GetCurrentProcessId(), r6pid };

			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_GET_BASEADDR, &hook_base_request);

			return base;
		}

		void set_wnd_thread(HWND window, UINT_PTR lpThreadInfo)
		{
			HOOK_RENDERER_REQUEST renderer_request;
			renderer_request.hwnd = (UINT_PTR)window;
			renderer_request.lpThreadInfo = lpThreadInfo;
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_RENDERER_SET_WND_THREAD, &renderer_request);
		}

		UINT_PTR get_wnd_thread(HWND window)
		{
			UINT_PTR info = 0;

			HOOK_RENDERER_REQUEST renderer_request;
			renderer_request.hwnd = (UINT_PTR)window;
			renderer_request.UserBufferAdress = (uint64_t)&info;
			renderer_request.UserPID = (uint32_t)GetCurrentProcessId();
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_RENDERER_GET_WND_THREAD, &renderer_request);
			return info;
		}

		template <typename T>
			T rvm(std::uintptr_t address)
		{
			_HOOK_READ_REQUEST read;

			read.Address = address;
			read.Size = sizeof(T);
			read.ProcessId = r6pid;


			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_READ, &read);

			return *(T*)&read.Response;
		}


		void WriteVirtualMemoryRaw(uint64_t WriteAddress, uint64_t SourceAddress, SIZE_T WriteSize)
		{
			HOOK_WRITE_REQUEST  WriteRequest;
			WriteRequest.ProcessId = r6pid;
			WriteRequest.Address = WriteAddress;
			WriteRequest.Value = SourceAddress;
			WriteRequest.Size = WriteSize;


			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_WRITE, &WriteRequest);
		}

		template <typename T>
		 void wvm(std::uintptr_t address, T& buffer)
		{
			WriteVirtualMemoryRaw(address, (uint64_t)&buffer, sizeof(T));
		}

		template <typename Type>
		bool IsValidPtr(Type* ptr)
		{
			return (ptr && sizeof(ptr)) ? true : false;
		}
private:
	ParalyzeCheatMemory();
	~ParalyzeCheatMemory();

	static ParalyzeCheatMemory* m_pInstance;
};