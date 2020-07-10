#include "RegistryInfoHelper.h"
#include "../MetaStr.h"
#include <string>
#include <atlbase.h>
#include <Wbemidl.h>
#include <codecvt>
#include <comdef.h>
#include "../utils.h"

#pragma comment(lib, "wbemuuid.lib")

namespace RegistryInfoHelper
{
	std::wstring ReadRegValue(HKEY root, std::wstring key, std::wstring name)
	{
		HKEY hKey;
		RegOpenKeyExA(root, util::ws2s(key).c_str(), 0, KEY_READ, &hKey);
		DWORD type;
		DWORD cbData = 100;
		if (RegQueryValueExA(hKey, util::ws2s(name).c_str(), NULL, &type, NULL, &cbData) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
		}
		if (type != REG_SZ)
		{
			RegCloseKey(hKey);
		}
		char value1[100];
		if (RegQueryValueExA(hKey, util::ws2s(name).c_str(), NULL, NULL, (LPBYTE)&value1, &cbData) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
		}
		std::string temp1 = std::string(value1);
		std::wstring value = util::s2ws(temp1);
		RegCloseKey(hKey);
		size_t firstNull = value.find_first_of(L'\0');
		if (firstNull != std::string::npos)
			value.resize(firstNull);

		return value;
	}



	std::string get_HwProfileGuid()
	{
		std::string reg_part1 = ("SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001");
		std::string reg_part2 = ("HwProfileGuid");
		std::wstring whwid = ReadRegValue(HKEY_LOCAL_MACHINE, util::s2ws(reg_part1), util::s2ws(reg_part2));
		std::string HwProfileGuid(whwid.begin(), whwid.end());
		return HwProfileGuid;
	}

	std::string get_Win32_PhysicalMemory()
	{
		HRESULT hr;
		hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL, EOAC_NONE, NULL);
		CComPtr<IWbemLocator> pWbemLocator;
		hr = pWbemLocator.CoCreateInstance(CLSID_WbemLocator);
		CComPtr<IWbemServices> pWbemServices;
		hr = pWbemLocator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, NULL, &pWbemServices);
		CComPtr<IEnumWbemClassObject> pEnum;
		std::string part1 = ("Select PartNumber FROM Win32_PhysicalMemory WHERE PartNumber IS NOT NULL");
		CComBSTR cbsQuery = util::s2ws(part1).c_str();
		hr = pWbemServices->ExecQuery(_bstr_t("WQL"), cbsQuery, WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
		ULONG uObjectCount = 0;
		CComPtr<IWbemClassObject> pWmiObject;
		hr = pEnum->Next(WBEM_INFINITE, 1, &pWmiObject, &uObjectCount);
		CComVariant cvtVersion;
		if (uObjectCount != 0) {
			hr = pWmiObject->Get(L"PartNumber", 0, &cvtVersion, 0, 0);
			std::wstring ws(cvtVersion.bstrVal, SysStringLen(cvtVersion.bstrVal));
			std::string sOsVersion = util::ws2s(ws);
			return sOsVersion;
		}
		return ("Win32_PhysicalMemoryFAILED");
	}

	std::string get_OA3xOriginalProductKey()
	{
		HRESULT hr;
		hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL, EOAC_NONE, NULL);
		CComPtr<IWbemLocator> pWbemLocator;
		hr = pWbemLocator.CoCreateInstance(CLSID_WbemLocator);
		CComPtr<IWbemServices> pWbemServices;
		hr = pWbemLocator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, NULL, &pWbemServices);
		CComPtr<IEnumWbemClassObject> pEnum;
		std::string part1 = ("Select OA3xOriginalProductKey FROM SoftwareLicensingService");
		CComBSTR cbsQuery = util::s2ws(part1).c_str();
		hr = pWbemServices->ExecQuery(_bstr_t("WQL"), cbsQuery, WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
		ULONG uObjectCount = 0;
		CComPtr<IWbemClassObject> pWmiObject;
		hr = pEnum->Next(WBEM_INFINITE, 1, &pWmiObject, &uObjectCount);
		CComVariant cvtVersion;
		if (uObjectCount != 0) {
			hr = pWmiObject->Get(L"OA3xOriginalProductKey", 0, &cvtVersion, 0, 0);
			std::wstring ws(cvtVersion.bstrVal, SysStringLen(cvtVersion.bstrVal));
			std::string sOsVersion = util::ws2s(ws);
			return sOsVersion;
		}
		return ("OA3xOriginalProductKeyFAILED");
	}

	std::string get_Win32_BaseBoard()
	{
		HRESULT hr;
		hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL,
			RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL, EOAC_NONE, NULL);
		CComPtr<IWbemLocator> pWbemLocator;
		hr = pWbemLocator.CoCreateInstance(CLSID_WbemLocator);
		CComPtr<IWbemServices> pWbemServices;
		hr = pWbemLocator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, NULL, &pWbemServices);
		CComPtr<IEnumWbemClassObject> pEnum;
		std::string part1 = ("Select SerialNumber from Win32_BaseBoard");
		CComBSTR cbsQuery = util::s2ws(part1).c_str();
		hr = pWbemServices->ExecQuery(_bstr_t("WQL"), cbsQuery, WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
		ULONG uObjectCount = 0;
		CComPtr<IWbemClassObject> pWmiObject;
		hr = pEnum->Next(WBEM_INFINITE, 1, &pWmiObject, &uObjectCount);
		CComVariant cvtVersion;
		if (uObjectCount != 0) {
			hr = pWmiObject->Get(L"SerialNumber", 0, &cvtVersion, 0, 0);
			std::wstring ws(cvtVersion.bstrVal, SysStringLen(cvtVersion.bstrVal));
			std::string sOsVersion = util::ws2s(ws);
			return sOsVersion;
		}
		return ("Win32_BaseBoardFAILED");
	}




}

