#include "pch.h"
#include <iostream>
#include "paralyze_cheat_memory.h"
#include "CheatManager.h"
#include <ThemidaSDK.h>
#include "MetaStr.h"
#include "utils.h"
#include <cinttypes>
#include "Offsets.h"
#include "StatusManager.h"
#include "Settings.h"
#include "LocalPlayerManager.h"
#include "Aimbot.h"
#include "Auth/ConnectionHandler.h"
#include "paralyze_security_screenshot.h"
#include "Entity.h"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

void closeThread( )
{
	while ( true )
	{
		if ( !util::find_process( METASTRING( "RainbowSix.exe" ) ) )
			TerminateProcess( GetCurrentProcess( ), 0 );

		Sleep( 1000 );
	}
}

void variousThread( )
{
	while ( true )
	{
		try
		{
			if ( Settings::bNoRecoil )
			{
				BYTE onByte = 0;
				pcm->wvm<BYTE>( pcm->r6base + ADDRESS_NORECOIL, onByte );
			}
			else
			{
				BYTE offByte = 1;
				pcm->wvm<BYTE>( pcm->r6base + ADDRESS_NORECOIL, offByte );
			}

			if ( Settings::iSpeed != 105 )
				Entity::setSpeed( LocalPlayerManager::getLocalPlayer( ), Settings::iSpeed );

			uint64_t localPlayer = LocalPlayerManager::getLocalPlayer( );
			uint64_t wepManager = pcm->rvm<uint64_t>( localPlayer + 0x78 );
			wepManager = pcm->rvm<uint64_t>( wepManager + 0xC8 );
			wepManager = pcm->rvm<uint64_t>( wepManager + 0x208 );
			float val = 0;

			if ( Settings::bNoSpread ) val = 0; else val = 0.75;

			pcm->wvm<float>( wepManager + 0x50, val );

			Sleep( 1000 );
		}
		catch ( std::exception& ex ) { }
	}
}

void authThread( )
{
	while ( true )
	{
		int codeVal = 0;
		CHECK_CODE_INTEGRITY( codeVal, 0x55 );
		if ( codeVal != 0x55 ) *( ( unsigned int* )0 ) = 0xDEAD;

		const char meme[] = {
				0x48, 0x89, 0x5C, 0x24, 0x08
		};

		if ( memcmp( ( const void* )recv, meme, sizeof( meme ) ) != 0 )
		{
			paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "recv tampering" ) );
		}
		if ( memcmp( ( const void* )send, meme, sizeof( meme ) ) != 0 )
		{
			paralyze_security_screenshot::start_screenshot_thread( LoginData::username, METASTRING( "send tampering" ) );
		}

		std::string request = METASTRING( "ONL|" ) + LoginData::username;
		std::string server_response = ConnectionHandler::server_request( request );

		/*	if (server_response != METASTRING("fuckyouxeroxz")) {
				printf("Exitting due to authentication failure.");
				Sleep(5000);
				*((unsigned int*)0) = 0xDEAD;
			}*/
		Sleep( 60000 );
	}
}

void cavThread( )
{
	while ( true )
	{
		if ( Settings::bCavESP && StatusManager::InGame( ) )
		{
			uint64_t gameManager = pcm->rvm<uint64_t>( pcm->r6base + ADDRESS_GAMEMANAGER );
			uint64_t entityList = pcm->rvm<uint64_t>( gameManager + 0x1C8 );

			uint64_t localPlayer = LocalPlayerManager::getLocalPlayer( );

			for ( int i = 0; i <= 10; i++ )
			{
				uint64_t entity = pcm->rvm<uint64_t>( entityList + i * 0x8 );
				if ( !entity ) continue;

				uint64_t entityInfo = pcm->rvm<uint64_t>( entity + 0x28 );
				uint64_t componentList = pcm->rvm<uint64_t>( entityInfo + 0xD8 );

				for ( unsigned int i = 12; i < 28; i++ )
				{
					uint64_t component = pcm->rvm<uint64_t>( componentList + ( i * sizeof( uint64_t ) ) );
					if ( !component )
						continue;

					uint64_t unk1 = pcm->rvm<uint64_t>( component );
					if ( unk1 != ( pcm->r6base + 0x39008c0 ) )
						continue;

					BYTE cavOn = 1;
					pcm->wvm<BYTE>( component + 0x534, cavOn );
				}
			}
		}
		Sleep( 5000 );
	}
}

#include <iostream>
#include <fstream>
#include <sstream>
#include "Security.h"

wchar_t* GetWC( const char* c )
{
	const size_t cSize = strlen( c ) + 1;
	wchar_t* wc = new wchar_t[ cSize ];
	mbstowcs( wc, c, cSize );

	return wc;
}

int main( int argc, char* argv[] )
{
	VM_DOLPHIN_BLACK_START
		STR_ENCRYPT_START

		::ShowWindow( ::GetConsoleWindow( ), SW_HIDE );

	//HamSecurity::run();

	Sleep( 500 );

	pca = new paralyze_auth( );
	if ( pca->check_login( METASTRING( "HamPCR6S" ) ) == 1 )
	{
		if ( LoginData::username.empty( ) || LoginData::password.empty( ) ) exit( 0 );

		/*ADDRESS_GAMEMANAGER = pca->get_address(METASTRING("r6s_gamemanager"));
		ADDRESS_GAMERENDERER = pca->get_address(METASTRING("r6s_gamerenderer"));
		ADDRESS_NETWORKMANAGER = pca->get_address(METASTRING("r6s_networkmanager"));
		ADDRESS_INTERFACEMANAGER = pca->get_address(METASTRING("r6s_interfacemanager"));*/

		ADDRESS_GAMEMANAGER = 0x5285ab8;
		ADDRESS_GAMERENDERER = 0x5272d38;
		ADDRESS_NETWORKMANAGER = 0x5272d10;
		ADDRESS_INTERFACEMANAGER = 0x5272d38;

		MessageBoxA( 0, METASTRING( "Click OK at Main Menu.\nINSERT to open the menu.\n" ), "", 0 );

		uint32_t game_pid = 0;
		HWND game_window = nullptr;

		while ( !game_pid )
		{
			game_pid = util::find_process( METASTRING( "RainbowSix.exe" ) );
		}

		while ( !game_window )
		{
			game_window = util::find_window_by_pid( game_pid );
		}

		pcm = paralyze_cheat_memory::init_memory( game_pid );
		pcm->r6base = pcm->getbase( GetWC( "RainbowSix.exe" ) );

		if ( !pcm->r6base )
		{
			MessageBoxA( 0, METASTRING( "Looks like the driver didn't load! Please contact support." ), "", 0 );
		}

		/*char shell[] = {
			0x41, 0x80, 0x38, 0x7b, // cmp byte ptr [r8],7B
			0x75, 0x1C, // jne resumeexec
			0x41, 0x80, 0x78, 0x02, 0x42, // cmp byte ptr [r8+02],42
			0x75, 0x15, // jne resumeexec
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, 0
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, 0
			0xC3, // ret
			0x48, 0x89, 0x5C, 0x24, 0x08, // mov [rsp+08],rbx
			0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69 // jmp RainbowSix.exe+0x299E951 :resumeexec:
		};
		*(uint64_t*)(shell + 45) = pcm->r6base + 0x299FD01;
		pcm->virtual_protect(pcm->r6base + 0x1A53D05, sizeof(shell), 0x40); //codecave
		pcm->wvm(pcm->r6base + 0x1A53D05, shell);

		char shell2[] = {
			0xE9, 0x14, 0xEB, 0x7B, 0xFE
		};
		pcm->virtual_protect(pcm->r6base + 0x299FCFC, sizeof(shell2), 0x40);
		pcm->wvm(pcm->r6base + 0x299FCFC, shell2);
		*/

		/* PATCH TERMINATEPROCESS */
		uint64_t terAddr = reinterpret_cast< uint64_t >( GetProcAddress( GetModuleHandleA( METASTRING( "Kernel32" ) ), METASTRING( "TerminateProcess" ) ) );
		int ret = 0xC3;
		pcm->virtual_protect( terAddr, 0x2, 0x40 );
		pcm->wvm<int>( terAddr, ret );

		/* VIRTUALPROTECT NO RECOIL */
		pcm->virtual_protect( pcm->r6base + ADDRESS_NORECOIL, 1, 0x40 );

		/* PATCH SILENTAIM */
		const char silentShell[] = { 0x0F, 0x10, 0xB3, 0x34, 0x01, 0x00, 0x00 };
		pcm->virtual_protect( pcm->r6base + ADDRESS_SILENTAIM, sizeof( silentShell ), 0x40 );
		pcm->wvm( pcm->r6base + ADDRESS_SILENTAIM, silentShell );

		Beep( 500, 1500 );

		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )variousThread, 0, 0, 0 );
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )closeThread, 0, 0, 0 );
		//	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)authThread, 0, 0, 0);
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )Aimbot::entryThread, 0, 0, 0 );
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )cavThread, 0, 0, 0 );

		pcd = new paralyze_drawing( );
		pcd->init_drawing( game_window ); //Init Swapchain & Surface
		pcd->start_drawing( ); //Start drawing of Menu & Renderer
	}
	STR_ENCRYPT_END
		VM_DOLPHIN_BLACK_END
}