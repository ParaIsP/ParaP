#pragma once
#include <Windows.h>
#include <iterator>
#include <map>
#include <thread>
#include "paralyze_security_screenshot.h"
#include "utils.h"
#include <winternl.h>
#include <ThemidaSDK.h>
#include <TlHelp32.h>
#include "MetaStr.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace HamSecurity
{
	void CheckProcessDebugFlags( )
	{
		typedef int ( WINAPI* pNtQueryInformationProcess )
			( HANDLE, UINT, PVOID, ULONG, PULONG );

		DWORD NoDebugInherit = 0;
		int Status;

		pNtQueryInformationProcess NtQIP = ( pNtQueryInformationProcess )
			GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
							"NtQueryInformationProcess" );

		while ( true )
		{
			Status = NtQIP( GetCurrentProcess( ),
							0x1f, // ProcessDebugFlags
							&NoDebugInherit, sizeof( NoDebugInherit ), NULL );

			if ( Status != 0x00000000 )
				continue;

			if ( NoDebugInherit == FALSE )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "CheckProcessDebugFlags" );
			}

			Sleep( 15000 );
		}
	}

	void CheckProcessDebugPort( )
	{
		typedef int ( WINAPI* pNtQueryInformationProcess )
			( HANDLE, UINT, PVOID, ULONG, PULONG );

		DWORD_PTR DebugPort = 0;
		ULONG ReturnSize = 0;
		int Status;

		pNtQueryInformationProcess NtQIP = ( pNtQueryInformationProcess )
			GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
							"NtQueryInformationProcess" );

		while ( true )
		{
			Status = NtQIP( GetCurrentProcess( ),
							0x7, // ProcessDebugPort
							&DebugPort, sizeof( DebugPort ), &ReturnSize );

			if ( Status != 0x00000000 )
				continue;

			if ( DebugPort )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "CheckProcessDebugPort" );
			}

			Sleep( 15000 );
		}
	}

	void CheckProcessDebugObjectHandle( )
	{
		typedef int ( WINAPI* pNtQueryInformationProcess )
			( HANDLE, UINT, PVOID, ULONG, PULONG );

		DWORD_PTR DebugHandle = 0;
		int Status;
		ULONG ReturnSize = 0;

		// Get NtQueryInformationProcess
		pNtQueryInformationProcess NtQIP = ( pNtQueryInformationProcess )
			GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
							"NtQueryInformationProcess" );

		while ( true )
		{
			Status = NtQIP( GetCurrentProcess( ),
							30, // ProcessDebugHandle
							&DebugHandle, sizeof( DebugHandle ), &ReturnSize );

			if ( Status != 0x00000000 )
			{
				continue;
			}

			if ( DebugHandle )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "CheckProcessDebugObjectHandle" );
			}

			Sleep( 15000 );
		}
	}

	bool HideFromDebugger( )
	{
		typedef NTSTATUS( NTAPI* NT_SET_INFORMATION_THREAD )(
			IN HANDLE ThreadHandle,
			IN ULONG ThreadInformationClass,
			IN PVOID ThreadInformation,
			IN ULONG ThreadInformationLength
			);
		NT_SET_INFORMATION_THREAD NtSIT = ( NT_SET_INFORMATION_THREAD )
			GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ),
							"NtSetInformationThread" );

		while ( true )
		{
			NtSIT( GetCurrentThread( ),
				   0x11, //ThreadHideFromDebugger
				   0,
				   0 );

			Sleep( 15000 );
		}
	}

	void CheckSystemDebugger( )
	{
		typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
		{
			BOOLEAN DebuggerEnabled;
			BOOLEAN DebuggerNotPresent;
		} SYSTEM_KERNEL_DEBUGGER_INFORMATION, * PSYSTEM_KERNEL_DEBUGGER_INFORMATION;
		enum SYSTEM_INFORMATION_CLASS { SystemKernelDebuggerInformation = 35 };
		typedef NTSTATUS( __stdcall* ZW_QUERY_SYSTEM_INFORMATION )( IN SYSTEM_INFORMATION_CLASS SystemInformationClass, IN OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength );
		ZW_QUERY_SYSTEM_INFORMATION ZwQuerySystemInformation;
		SYSTEM_KERNEL_DEBUGGER_INFORMATION Info;
		ZwQuerySystemInformation = ( ZW_QUERY_SYSTEM_INFORMATION )GetProcAddress( GetModuleHandleA( "ntdll.dll" ), "ZwQuerySystemInformation" );

		while ( true )
		{
			if ( ZwQuerySystemInformation && ZwQuerySystemInformation( SystemKernelDebuggerInformation, &Info, sizeof( Info ), NULL ) )
			{
				if ( Info.DebuggerEnabled || !Info.DebuggerNotPresent )
				{
					paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "CheckSystemDebugger" );
				}
			}

			Sleep( 15000 );
		}
	}

	void isDbgPresent( )
	{
		while ( true )
		{
			if ( IsDebuggerPresent( ) )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "IsDebuggerPresent" );
			}

			PBOOL isDebugged = ( PBOOL )false;
			CheckRemoteDebuggerPresent( GetCurrentProcess( ), isDebugged );
			if ( isDebugged )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "CheckRemoteDebuggerPresent" );
			}

			Sleep( 15000 );
		}
	}

	int severalDetect( )
	{
		while ( true )
		{
			if ( GetModuleHandleA( METASTRING( "apimonitor-drv-x64.sys" ) ) )
			{ // API Monitor v2
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "apimonitor-drv-x64.sys" ) );
			}

			if ( GetModuleHandleA( METASTRING( "vehdebug-x86_64.dll" ) ) )
			{ // Cheat Engine Debugger (VEH)
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "vehdebug-x86_64.dll" ) );
			}

			Sleep( 15000 );
		}
	}

	void recvCheck( )
	{
		VM_TIGER_BLACK_START
			const char recvSig[ 201 ] = {};
		memcpy( ( void* )recvSig, ( void* )recv, sizeof( recvSig ) );

		while ( true )
		{
			if ( memcmp( ( void* )recvSig, ( void* )recv, sizeof( recvSig ) ) != 0 )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "recvCheck" );
			}

			Sleep( 15000 );
		}
		VM_TIGER_BLACK_END
	}

	void checkScyllaHide( )
	{
		while ( true )
		{
			uint64_t NtSetInformationThread_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "ntdll" ), METASTRING( "NtSetInformationThread" ) ) );
			byte NtOne = *( byte* )( NtSetInformationThread_addr );
			byte NtTwo = *( byte* )( NtSetInformationThread_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtQueryObject_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "ntdll" ), METASTRING( "NtQueryObject" ) ) );
			NtOne = *( byte* )( NtQueryObject_addr );
			NtTwo = *( byte* )( NtQueryObject_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtYieldExecution_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "ntdll" ), METASTRING( "NtYieldExecution" ) ) );
			NtOne = *( byte* )( NtYieldExecution_addr );
			NtTwo = *( byte* )( NtYieldExecution_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtCreateThreadEx_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "ntdll" ), METASTRING( "NtCreateThreadEx" ) ) );
			NtOne = *( byte* )( NtCreateThreadEx_addr );
			NtTwo = *( byte* )( NtCreateThreadEx_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t OutputDebugStringA_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "KERNELBASE" ), METASTRING( "OutputDebugStringA" ) ) );
			NtOne = *( byte* )( OutputDebugStringA_addr );
			NtTwo = *( byte* )( OutputDebugStringA_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtUserFindWindowEx_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "win32u" ), METASTRING( "NtUserFindWindowEx" ) ) );
			NtOne = *( byte* )( NtUserFindWindowEx_addr );
			NtTwo = *( byte* )( NtUserFindWindowEx_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtUserBuildHwndList_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "win32u" ), METASTRING( "NtUserBuildHwndList" ) ) );
			NtOne = *( byte* )( NtUserBuildHwndList_addr );
			NtTwo = *( byte* )( NtUserBuildHwndList_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtUserQueryWindow_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "win32u" ), METASTRING( "NtUserQueryWindow" ) ) );
			NtOne = *( byte* )( NtUserQueryWindow_addr );
			NtTwo = *( byte* )( NtUserQueryWindow_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			uint64_t NtSetDebugFilterState_addr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( "ntdll" ), METASTRING( "NtSetDebugFilterState" ) ) );
			NtOne = *( byte* )( NtSetDebugFilterState_addr );
			NtTwo = *( byte* )( NtSetDebugFilterState_addr + 0x1 );

			if ( NtOne == 0x90 || NtOne == 0xFF || NtTwo == 0x90 || NtTwo == 0xFF )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "ScyllaHide" ) );
			}

			Sleep( 15000 );
		}
	}

	std::map<int, HANDLE> threads;

	void checkThreads( )
	{
		while ( true )
		{
			for ( auto const& x : threads )
			{
				if ( SuspendThread( x.second ) == 0x00000000FFFFFFFF )
				{ // could not suspend == thread is killed
					paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "Anti-Debugging thread killed" );
				}

				ResumeThread( x.second );
			}
			Sleep( 15000 );
		}
	}

	void checkRecv( )
	{
		Sleep( 5000 );
		while ( true )
		{
			const char meme[] = {
				0x48, 0x89, 0x5C, 0x24, 0x08
			};

			if ( memcmp( ( const void* )recv, meme, sizeof( meme ) ) != 0 )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "recv tampering" );
			}
			if ( memcmp( ( const void* )send, meme, sizeof( meme ) ) != 0 )
			{
				paralyze_security_screenshot::start_screenshot_thread( LoginData::username, "send tampering" );
			}
			Sleep( 15000 );
		}
	}

	std::vector<std::string> get_credentials( )
	{
		std::string path = METASTRING( "C:/Users/" ) + util::get_computer_username( ) + METASTRING( "/OK2sRbtxYM" );
		if ( util::fexists( path.c_str( ) ) )
		{
			std::ifstream ifs( path.c_str( ) );
			std::string content( ( std::istreambuf_iterator<char>( ifs ) ), ( std::istreambuf_iterator<char>( ) ) );
			path.clear( );
			return util::split( content, '|' );
		}
		return std::vector<std::string> {METASTRING( "fail" ), METASTRING( "fail" )};
	}

	void run( )
	{
		//threads.insert(std::pair<int, HANDLE>(0, CreateThread(0, 0, (LPTHREAD_START_ROUTINE)isDbgPresent, 0, 0, 0)));
		threads.insert( std::pair<int, HANDLE>( 1, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )severalDetect, 0, 0, 0 ) ) );
		//threads.insert(std::pair<int, HANDLE>(2, CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recvCheck, 0, 0, 0)));
		//threads.insert(std::pair<int, HANDLE>(3, CreateThread(0, 0, (LPTHREAD_START_ROUTINE)kernel32Check, 0, 0, 0)));
		threads.insert( std::pair<int, HANDLE>( 4, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )CheckProcessDebugFlags, 0, 0, 0 ) ) );
		threads.insert( std::pair<int, HANDLE>( 5, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )CheckProcessDebugPort, 0, 0, 0 ) ) );
		threads.insert( std::pair<int, HANDLE>( 6, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )CheckProcessDebugObjectHandle, 0, 0, 0 ) ) );
		threads.insert( std::pair<int, HANDLE>( 7, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )HideFromDebugger, 0, 0, 0 ) ) );
		threads.insert( std::pair<int, HANDLE>( 8, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )CheckSystemDebugger, 0, 0, 0 ) ) );
		threads.insert( std::pair<int, HANDLE>( 9, CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )checkScyllaHide, 0, 0, 0 ) ) );
		//threads.insert(std::pair<int, HANDLE>(10, CreateThread(0, 0, (LPTHREAD_START_ROUTINE)patchInjection, 0, 0, 0)));

		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )checkThreads, 0, 0, 0 );
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)checkRecv, 0, 0, 0);
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )checkScyllaHide, 0, 0, 0 );

		Sleep( 2000 );

		VM_DOLPHIN_BLACK_START
			const char sendShell[] = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x57, 0x41, 0x56, 0x41, 0x57, 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69 };
		*( uint64_t* )( sendShell + 26 ) = ( uint64_t )send + 0x14;
		LPVOID allocatedShell = VirtualAlloc( NULL, sizeof( sendShell ), 0x00001000, PAGE_EXECUTE_READWRITE );
		memcpy( ( void* )allocatedShell, ( void* )sendShell, sizeof( sendShell ) );
		sendAC = ( send_call )( allocatedShell );

		if ( util::find_process( METASTRING( "Wireshark.exe" ) ) )
		{
			LoginData::username = get_credentials( ).at( 0 );
			MessageBoxA( 0, METASTRING( "Disable Wireshark to continue." ), "", MB_ICONERROR );
			paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "Wireshark" ) );
			Sleep( 99999999 );
		}

		LPVOID drivers[ 250 ];
		DWORD cbNeeded;
		int cDrivers, i;
		if ( EnumDeviceDrivers( drivers, sizeof( drivers ), &cbNeeded ) && cbNeeded < sizeof( drivers ) )
		{
			TCHAR szDriver[ 250 ];

			cDrivers = cbNeeded / sizeof( drivers[ 0 ] );
			for ( i = 0; i < cDrivers; i++ )
			{
				if ( GetDeviceDriverBaseName( drivers[ i ], szDriver, sizeof( szDriver ) / sizeof( szDriver[ 0 ] ) ) )
				{
					std::basic_ostringstream<TCHAR> its;
					its << METASTRING( "npcap.sys" );
					std::basic_string<TCHAR> ts = its.str( );

					if ( _tcsstr( szDriver, ts.c_str( ) ) )
					{
						LoginData::username = get_credentials( ).at( 0 );
						MessageBoxA( 0, METASTRING( "Disable Wireshark to continue." ), "", MB_ICONERROR );
						paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "Wireshark" ) );
						Sleep( 99999999 );
					}
				}
			}
		}
		VM_DOLPHIN_BLACK_END
	}
}