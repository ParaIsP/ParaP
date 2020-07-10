#pragma once
#include <string>

namespace ComputerIdentifier
{
	struct RegistryInformation
	{
		std::string HwProfileGuid;
		std::string Win32_BaseBoard;
		std::string Win32_PhysicalMemory;
	};

	struct HardInformation
	{
		std::string computer_username;
		std::string computer_name;
		std::string processor_name;
		std::string d3d_information;
	};

	struct ComputerIdentifierInformation
	{
		RegistryInformation registry_information;
		HardInformation hard_information;
	};

	std::string get_hwid();
	std::string getSHA1(std::string instr);
	ComputerIdentifierInformation get_computer_identifier_information();

}
