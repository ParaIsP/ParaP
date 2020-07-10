#include "ComputerIdentifier.h"
#include "RegistryInfoHelper.h"
#include <string>
#include "HardInfoHelper.h"
#include <iostream>
#include "../Encryption/AesCryptoHandler.h"
#include "../Auth/sha1.h"
#include "../MetaStr.h"


//#define PCHWIDDEBUG


namespace ComputerIdentifier
{
	RegistryInformation get_registryinfo()
	{
		RegistryInformation registry_information;
		//registry_information.HwProfileGuid = RegistryInfoHelper::get_HwProfileGuid();
		//registry_information.Win32_BaseBoard = RegistryInfoHelper::get_Win32_BaseBoard();
		registry_information.Win32_PhysicalMemory = RegistryInfoHelper::get_Win32_PhysicalMemory();

		return registry_information;
	}

	HardInformation get_hardinfo()
	{
		HardInformation hard_information;
		//hard_information.processor_name = HardInfoHelper::get_processor_name();
		//hard_information.computer_username = HardInfoHelper::get_username();
		//hard_information.computer_name = HardInfoHelper::get_computer_name();
		//hard_information.d3d_information = HardInfoHelper::get_d3d_information();

		return hard_information;
	}

	ComputerIdentifierInformation get_computer_identifier_information()
	{
		ComputerIdentifierInformation computer_identifier_information;
		computer_identifier_information.registry_information = get_registryinfo();
		computer_identifier_information.hard_information = get_hardinfo();
		return computer_identifier_information;
	}

	std::string get_hwid()
	{
		ComputerIdentifierInformation information = get_computer_identifier_information();

		std::string computer_information;

#ifdef PCHWIDDEBUG
		std::cout << "ComputerUsername: " << information.hard_information.computer_username << std::endl;
		std::cout << "ComputerName: " << information.hard_information.computer_name << std::endl;
		std::cout << "CPUName: " << information.hard_information.processor_name << std::endl;
		std::cout << "D3DInfo: " << information.hard_information.d3d_information << std::endl;
		std::cout << "MBID: " << information.registry_information.Win32_BaseBoard << std::endl;
		std::cout << "GUID: " << information.registry_information.HwProfileGuid << std::endl;
		std::cout << "RAMID: " << information.registry_information.Win32_PhysicalMemory << std::endl;
#endif

		//computer_information.append(information.hard_information.computer_username);
		computer_information.append(METASTRING("reallyhavetoimprovethis|"));
		/*computer_information.append("|");
		//computer_information.append(information.hard_information.computer_name);
		computer_information.append("");
		computer_information.append("|");
		//computer_information.append(information.hard_information.processor_name);
		computer_information.append("");
		computer_information.append("|");
		//computer_information.append(information.hard_information.d3d_information);
		computer_information.append("");
		computer_information.append("|");
		//computer_information.append(information.registry_information.Win32_BaseBoard);
		computer_information.append("");
		computer_information.append("|");
		//computer_information.append(information.registry_information.HwProfileGuid);
		computer_information.append("");
		computer_information.append("|");*/
		computer_information.append(information.registry_information.Win32_PhysicalMemory);

		/*HANDLE hFile1;
		FILETIME ftCreate;
		SYSTEMTIME stUTC, stLocal;
		hFile1 = CreateFile(L"C:\\Windows\\‪bfsvc.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		GetFileTime(hFile1, &ftCreate, NULL, NULL);
		FileTimeToSystemTime(&ftCreate, &stUTC);
		computer_information.append("|");
		computer_information.append((char*)ftCreate.dwLowDateTime);
		*/
		return computer_information;
	}

	std::string toString2(const char* data, int len)
	{
		std::string buffAsStdStr;
		for (int i = 0; i < len; i++)
		{
			char buff[100];
			snprintf(buff, sizeof(100), "%02X", (unsigned char)data[i]);
			buffAsStdStr += buff;
		}

#ifdef PCHWIDDEBUG
		std::cout << "buffAsStdStr: " << buffAsStdStr << std::endl;
#endif	
		return buffAsStdStr;
	}

	std::string getSHA1(std::string instr) {
		std::vector<unsigned char> hash(picosha2::k_digest_size);
		picosha2::hash256(instr.begin(), instr.end(), hash.begin(), hash.end());

		std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
		return hex_str;
	}

}