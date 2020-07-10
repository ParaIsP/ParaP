#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <apiquery2.h>
#include <consoleapi2.h>
#include <processthreadsapi.h>
#include <libloaderapi.h>
#include "MetaStr.h"

class paralyze_cheat_memory
{
public:


	DWORD r6pid;
	uint64_t r6base;
	uint64_t uplay_base;
	uint64_t kernel32_base;

	typedef struct _HOOK_READ_REQUEST
	{
		ULONG ProcessId;

		ULONGLONG Address;
		void* Response;
		ULONGLONG Size;
	} HOOK_READ_REQUEST, * PHOOK_READ_REQUEST;

	typedef struct _HOOK_READ2_REQUEST
	{
		ULONG ProcessId;
		UINT_PTR Value;
		UINT_PTR Address;
		ULONGLONG Size;
	} HOOK_READ2_REQUEST, * PHOOK_READ2_REQUEST;

	typedef struct _HOOK_WRITE_REQUEST
	{
		ULONG ProcessId;

		UINT_PTR Value;
		UINT_PTR Address;
		ULONG Size;

	} HOOK_WRITE_REQUEST, * PHOOK_WRITE_REQUEST;

	typedef struct _HOOK_RENDERER_REQUEST
	{
		UINT_PTR hwnd;
		UINT_PTR lpThreadInfo;
		ULONG     UserPID;
		ULONGLONG UserBufferAdress;
	} HOOK_RENDERER_REQUEST, * PHOOK_RENDERER_REQUEST;

	typedef struct _k_protect_mem_request {
		ULONG pid, protect;
		ULONGLONG addr;
		SIZE_T size;
		ULONG UserPID;
		ULONGLONG UserBufferAdress;
	} k_protect_mem_request, * pk_protect_mem_request;


	enum PROTO_MESSAGE {
		PROTO_GET_BASEADDR = 7,
		PROTO_NORMAL_READ = 55,
		PROTO_NORMAL_WRITE = 33,
		PROTO_RENDERER_GET_WND_THREAD = 66,
		PROTO_RENDERER_SET_WND_THREAD = 44,
		PROTO_UNHOOK = 32,
		PROTO_NORMAL_READ_UNSAFE = 79,
		PROTO_NORMAL_WRITE_UNSAFE = 12,
		PROTO_COPY_MEMORY = 43,
		PROTO_BUFFER_READ = 46,
		PROTO_PROTECT_VMEM = 65,
		PROTO_CLEAN_ALL = 99,
	};

	typedef struct _HOOK_BASE_REQUEST
	{
		ULONGLONG UserBufferAdress;
		ULONGLONG ReadSize;
		ULONG     UserPID;
		ULONG     GamePID;
		wchar_t* uplay;
	} HOOK_BASE_REQUEST, * PHOOK_BASE_REQUEST;


	int64_t getbase(wchar_t* moduleName)
	{
		try{
			int64_t base = 0;
			HOOK_BASE_REQUEST hook_base_request{ (uint64_t)&base, sizeof(int64_t), (uint32_t)GetCurrentProcessId(), r6pid,moduleName };

			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_GET_BASEADDR, &hook_base_request);
			return base;
		}
		catch (std::exception & ex) { return 0; }
	}

	void set_wnd_thread(HWND window, UINT_PTR lpThreadInfo)
	{
		try{
			HOOK_RENDERER_REQUEST renderer_request;
			renderer_request.hwnd = (UINT_PTR)window;
			renderer_request.lpThreadInfo = lpThreadInfo;
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_RENDERER_SET_WND_THREAD, &renderer_request);
		}
		catch (std::exception & ex) { return; }
	}

	UINT_PTR get_wnd_thread(HWND window)
	{
		try{
			UINT_PTR info = 0;

			HOOK_RENDERER_REQUEST renderer_request;
			renderer_request.hwnd = (UINT_PTR)window;
			renderer_request.UserBufferAdress = (uint64_t)&info;
			renderer_request.UserPID = (uint32_t)GetCurrentProcessId();
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_RENDERER_GET_WND_THREAD, &renderer_request);
			return info;
		}
		catch (std::exception & ex) { return 0; }
	}

	template <typename T>
	T rvm(std::uintptr_t address)
	{
		try{
			T buffer;
			_HOOK_READ_REQUEST read;

			read.Address = address;
			read.Size = sizeof(T);
			read.ProcessId = r6pid;

			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_READ, &read);

			return *(T*)&read.Response;
		}
		catch (std::exception & ex) { 
		}
	}

	template <typename T>
	T rvmbig(std::uintptr_t address)
	{
		try {
			T buffer;
			_HOOK_READ_REQUEST read;

			read.Address = address;
			read.Response = &buffer;
			read.Size = sizeof(T);
			read.ProcessId = r6pid;


			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_READ, &read);

			return *(T*)&read.Response;
		}
		catch (std::exception & ex) { return 0;  }
	}

	void ReadVirtualMemoryRaw(uint64_t ReadAddress, uint64_t TargetAddress, SIZE_T ReadSize)
	{
		try {
			HOOK_READ2_REQUEST  read2_request;
			read2_request.ProcessId = r6pid;
			read2_request.Address = ReadAddress;
			read2_request.Value = TargetAddress;
			read2_request.Size = ReadSize;
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_BUFFER_READ, &read2_request);
		}
		catch (std::exception & ex) { return;  }
	}

	template <typename T>
	T rvmunsafe(std::uintptr_t address)
	{
		try {
			_HOOK_READ_REQUEST read;

			read.Address = address;
			read.Size = sizeof(T);
			read.ProcessId = r6pid;


			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_READ_UNSAFE, &read);

			return *(T*)&read.Response;
		}
		catch (std::exception & ex) { return 0; }
	}


	void WriteVirtualMemoryRaw(uint64_t WriteAddress, uint64_t SourceAddress, SIZE_T WriteSize, bool unsafe)
	{
		try {
			HOOK_WRITE_REQUEST  WriteRequest;
			WriteRequest.ProcessId = r6pid;
			WriteRequest.Address = WriteAddress;
			WriteRequest.Value = SourceAddress;
			WriteRequest.Size = WriteSize;

			if (unsafe) {
				NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_WRITE_UNSAFE, &WriteRequest);
			}
			else
			{
				NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_NORMAL_WRITE, &WriteRequest);
			}
		}
		catch (std::exception & ex) { return; }
	}


	template <typename T>
	void wvm(std::uintptr_t address, T& buffer)
	{
		try {
			WriteVirtualMemoryRaw(address, (uint64_t)&buffer, sizeof(T), false);
		}
		catch (std::exception & ex) { return; }
	}

	template <typename T>
	void wvmunsafe(std::uintptr_t address, T& buffer)
	{
		try{
			WriteVirtualMemoryRaw(address, (uint64_t)&buffer, sizeof(T), true);
		}
		catch (std::exception & ex) { return; }
	}


	ULONG virtual_protect(uint64_t address, size_t size, uint32_t protect)
	{
		try {
			ULONG oldProt = 0;
			k_protect_mem_request request{ r6pid, protect, address, size,(uint32_t)GetCurrentProcessId(),(uint64_t)&oldProt };
			NtGdiDdDDINetDispStopMiracastDisplayDevice(PROTO_PROTECT_VMEM, &request);
			return oldProt;
		}catch(std::exception &ex){}
	}


	template <typename Type>
	bool IsValidPtr(Type* ptr)
	{
		return (ptr && sizeof(ptr)) ? true : false;
	}

	static paralyze_cheat_memory* init_memory(DWORD pid)
	{
		if (!m_pInstance)
			m_pInstance = new paralyze_cheat_memory();

		m_pInstance->r6pid = pid;

		return m_pInstance;
	}


private:
	paralyze_cheat_memory();
	~paralyze_cheat_memory();

	FARPROC fnNtQueryIntervalProfile = GetProcAddress(LoadLibraryA("win32u.dll"), METASTRING("NtTokenManagerCreateFlipObjectTokenHandle"));
	typedef HRESULT(__stdcall* tNtQueryIntervalProfile)(UINT_PTR test, HANDLE test2);
	tNtQueryIntervalProfile NtGdiDdDDINetDispStopMiracastDisplayDevice = reinterpret_cast<tNtQueryIntervalProfile>(fnNtQueryIntervalProfile);

	static paralyze_cheat_memory* m_pInstance;
};