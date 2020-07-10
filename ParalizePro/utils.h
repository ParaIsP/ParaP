#pragma once
#include <string>
#include <vector>
#include "Auth/paralyze_auth.h"

using send_call = int(*)(SOCKET     s,
	const char* buf,
	int        len,
	int        flags);

extern send_call sendAC;

namespace util {
	std::string ws2s(const std::wstring& wstr);
	std::wstring s2ws(const std::string& s);
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	std::string get_gmt_time_now();
	std::string get_gmt_minute_now();
	std::string get_gmt_date_now();
	std::vector<std::string> split(std::string strToSplit, char delimeter);
	std::string get_computer_username();
	bool fexists(const char *filename);
	uint32_t find_process(const std::string& Name);
	HWND find_window_by_pid(DWORD pid);
}

namespace LoginData
{
	extern std::string username;
	extern std::string password;
}

extern paralyze_auth* pca;