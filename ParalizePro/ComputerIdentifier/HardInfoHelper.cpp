#include "HardInfoHelper.h"
#include "../MetaStr.h"
#include <string>
#include <future>
#include <Iphlpapi.h>
#include <d3d9.h>
#include "../utils.h"

namespace HardInfoHelper
{
	std::string get_processor_name()
	{
		int CPUInfo[4] = { -1 };
		char CPUBrandString[0x40];
		__cpuid(CPUInfo, 0x80000000);
		unsigned int nExIds = CPUInfo[0];
		memset(CPUBrandString, 0, sizeof(CPUBrandString));
		for (int i = 0x80000000; i <= nExIds; ++i)
		{
			__cpuid(CPUInfo, i);
			if (i == 0x80000002)
				memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000003)
				memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000004)
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
		return util::ReplaceAll(std::string(CPUBrandString), " ", "");
	}

	std::string get_username()
	{
		wchar_t name[UNLEN + 1];
		DWORD size = UNLEN + 1;
		std::string UserName;
		if (GetUserNameW(name, &size))
		{
			std::wstring strname(name);
			UserName = util::ws2s(strname);
		}
		return UserName;
	}


	std::string get_computer_name()
	{
		wchar_t buffer[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
		DWORD cchBufferSize = sizeof(buffer) / sizeof(buffer[0]);
		if (!GetComputerNameW(buffer, &cchBufferSize))
			return "error";
		return util::ws2s(std::wstring(&buffer[0]));
	}

	std::string get_d3d_information()
	{
		LPDIRECT3D9 g_pD3D = NULL;
		//if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		//{
		//	return "error";
		//}
		D3DADAPTER_IDENTIFIER9 adapter;
		g_pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapter);
		std::string d3dinformation;
		d3dinformation.append(std::to_string(adapter.DeviceId)+"|");
		d3dinformation.append(std::string(adapter.DeviceName)+"|");
		d3dinformation.append(util::ReplaceAll(std::string(adapter.Description)," ","") +"|");
		d3dinformation.append(std::to_string(adapter.WHQLLevel)+"|");
		d3dinformation.append(std::to_string(adapter.VendorId)+"|");
		d3dinformation.append(std::to_string(adapter.SubSysId)+"|");
		d3dinformation.append(std::string(adapter.Driver)+"|");
		d3dinformation.append(std::to_string(adapter.Revision)+"|");
		return d3dinformation;
	}



}
