#include <Windows.h>
#include "utils.h"
#include <winnls.h>
#include <locale>
#include <codecvt>
#include <lmcons.h>
#include <winbase.h>
#include <Tlhelp32.h>
#include <sstream>
#include <fstream>
#include "MetaStr.h"
#include "Auth/paralyze_auth.h"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma warning(disable:4996)

using send_call = int(*)(SOCKET     s,
	const char* buf,
	int        len,
	int        flags);

send_call sendAC = 0;

namespace util {
	std::string get_gmt_time_now()
	{
		std::time_t now = std::time(0);
		struct tm newtime;
		gmtime_s(&newtime, &now);
		char buf[42];
		std::strftime(buf, 42, METASTRING("%H%d%M"), &newtime);
		return buf;
	}

	std::string get_gmt_date_now()
	{
		std::time_t now = std::time(0);
		struct tm newtime;
		gmtime_s(&newtime, &now);
		char buf[42];
		std::strftime(buf, 42, METASTRING("%d-%m-%Y_%H%M%S"), &newtime);
		return buf;
	}

	std::string get_gmt_minute_now()
	{
		std::time_t now = std::time(0);
		struct tm newtime;
		gmtime_s(&newtime, &now);
		char buf[42];
		std::strftime(buf, 42, METASTRING("%M"), &newtime);
		return buf;
	}

	std::string ws2s(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}
	std::vector<std::string> split(std::string strToSplit, char delimeter)
	{
		std::stringstream ss(strToSplit);
		std::string item;
		std::vector<std::string> splittedStrings;
		while (std::getline(ss, item, delimeter))
		{
			splittedStrings.push_back(item);
		}
		return splittedStrings;
	}
	std::string get_computer_username()
	{
		wchar_t name[UNLEN + 1];
		DWORD size = UNLEN + 1;
		std::string UserName;
		if (GetUserNameW(name, &size))
		{
			std::wstring strname(name);
			UserName = ws2s(strname);
		}
		return UserName;
	}
	bool fexists(const char *filename) {
		std::ifstream ifile(filename);
		return (bool)ifile;
	}
	uint32_t find_process(const std::string& Name) {
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		HANDLE ProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (Process32First(ProcessSnapshot, &ProcessEntry)) {
			do {
				if (!_stricmp(ws2s(std::wstring(ProcessEntry.szExeFile)).c_str(), Name.data()) && ProcessEntry.cntThreads > 2) {
					CloseHandle(ProcessSnapshot);
					return ProcessEntry.th32ProcessID;
				}
			} while (Process32Next(ProcessSnapshot, &ProcessEntry));
		}
		CloseHandle(ProcessSnapshot);
		return 0;
	}
	HWND find_window_by_pid(DWORD pid)
	{
		std::pair<HWND, DWORD> params = { 0, pid };
		BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			auto pParams = (std::pair<HWND, DWORD>*)(lParam);
			DWORD processId;
			if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
			{
				SetLastError(-1);
				pParams->first = hwnd;
				return FALSE;
			}
			return TRUE;
		}, (LPARAM)&params);

		if (!bResult && GetLastError() == -1 && params.first)
		{
			return params.first;
		}
		return 0;
	}
}

namespace LoginData
{
	std::string username = "";
	std::string password = "";
}

paralyze_auth* pca;