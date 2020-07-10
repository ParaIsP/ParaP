#include "ConnectionHandler.h"
#include <winsock.h>
#include <locale>
#include "../MetaStr.h"
#include <ThemidaSDK.h>
#include "../Encryption/AesCryptoHandler.h"

#pragma comment(lib, "ws2_32.lib")

namespace ConnectionHandler
{
	std::string server_request(std::string getrequest)
	{
		VM_SHARK_BLACK_START
		getrequest = AesCryptoHandler::encrypt(getrequest, "") + METASTRING("\n");
		WSADATA wsaData;
		SOCKET Socket;
		SOCKADDR_IN SockAddr;
		struct hostent* host;
		std::locale local;
		std::string website_HTML;

		std::string url = METASTRING("backend_srv.us.hammafia.co");

		WSAStartup(MAKEWORD(2, 2), &wsaData); // initialize socket

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		host = gethostbyname(url.c_str());

		SockAddr.sin_port = htons(18913);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

		connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
		send(Socket, getrequest.c_str(), strlen(getrequest.c_str()), 0);

		int Size;
		char* Filesize = new char[1024];

		if (recv(Socket, Filesize, 22, 0)) // File size
		{
			Size = atoi((const char*)Filesize);
		}

		char* Buffer = new char[Size];

		int Offset = 0;
		while (Size > Offset) {
			int Amount = recv(Socket, Buffer + Offset, Size - Offset, 0);

			if (Amount <= 0) {
				break;
			}
			else {
				Offset += Amount;
			}
		}

		struct sockaddr_in sin;
		int addrlen = sizeof(sin);
		int local_port = 0;
		if (getsockname(Socket, (struct sockaddr*) & sin, &addrlen) == 0 &&
			sin.sin_family == AF_INET &&
			addrlen == sizeof(sin))
		{
			local_port = ntohs(sin.sin_port);
		}

		std::string decrypted = AesCryptoHandler::aes_decrypt(Buffer, Size);
		closesocket(Socket);
		WSACleanup();

		VM_SHARK_BLACK_END
		return decrypted;
	}
}
