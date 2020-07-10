#include "paralyze_auth.h"
#include <vector>
#include "../MetaStr.h"
#include <fstream>
#include "sha1.h"
#include <ThemidaSDK.h>
#include "../Encryption/AesCryptoHandler.h"
#include "../ComputerIdentifier/ComputerIdentifier.h"
#include <random>
#include "ConnectionHandler.h"
#include <sstream>
#include "../utils.h"


bool logged_in = false;
bool loginOk = true;
std::string username = "";

//#define PCCRYPTODEBUG
//#define PCLOGINDEBUG

paralyze_auth::paralyze_auth()
{
}


paralyze_auth::~paralyze_auth()
{
}


std::vector<std::string> paralyze_auth::get_credentials()
{
	std::string path = METASTRING("C:/Users/OK2sRbtxYM");
	if (util::fexists(path.c_str())) {
		std::ifstream ifs(path.c_str());
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		path.clear();
		content = AesCryptoHandler::aes_decrypt((char*)content.c_str(), content.size());
		return util::split(content, '|');
	}
	return std::vector<std::string> {METASTRING("fail"), METASTRING("fail")};
}

std::string getPlaintext(std::string username, std::string password, std::string hwid, std::string cheat, int random, bool count)
{
	VM_SHARK_BLACK_START
		STR_ENCRYPT_START
		std::string plain = METASTRING("Q|");
	plain.append(username);
	plain.append(METASTRING("|"));
	plain.append(password);
	plain.append(METASTRING("|"));
	plain.append(hwid);
	plain.append(METASTRING("|"));
	plain.append(cheat);
	plain.append(METASTRING("|"));
	plain.append(std::to_string(random));
	if (count)
	{
		plain.append(METASTRING("|yes"));
	}

	STR_ENCRYPT_END
		VM_SHARK_BLACK_END
		return plain;
}

std::string getSHA1(std::string username, std::string password, std::string hwid, std::string cheat, int random)
{
	std::string sha1plain = username;
	sha1plain.append(METASTRING("|"));
	sha1plain.append(std::to_string(random));
	sha1plain.append(METASTRING("|"));
	sha1plain.append(password);
	sha1plain.append(cheat);
	sha1plain.append(hwid);


#ifdef PCCRYPTODEBUG
	std::cout << (sha1plain) << std::endl;
	std::cout << (sha_temp_1) << std::endl;
	std::cout << (sha_temp_2) << std::endl;
	std::cout << (sha_temp_3) << std::endl;
#endif

	return sha1plain;
}

int get_random_number()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 999343994);
	return dis(gen) + 9854;
}

int paralyze_auth::check_login(std::string cheat)
{
	VM_SHARK_BLACK_START
		std::vector<std::string> user_credentials = get_credentials();


	int auth_random = abs(get_random_number());
	int correct = auth_random * 33;
	std::string server_response = ConnectionHandler::server_request(getPlaintext(user_credentials.at(0), user_credentials.at(1), ComputerIdentifier::getSHA1(util::ReplaceAll(util::ReplaceAll(util::ReplaceAll(ComputerIdentifier::get_hwid(), "=", ""), "\n", ""), "\r", "")), cheat, auth_random, logged_in));


	if (server_response.find(METASTRING("UNE")) != std::string::npos) {
		return 0;
	}
	else if (server_response.find(METASTRING("WUOP")) != std::string::npos) {
		return -1;
	}
	else if (server_response.find(METASTRING("HWID")) != std::string::npos) {
		return -2;
	}
	else if (server_response.find(METASTRING("NAS")) != std::string::npos) {
		return -3;
	}
	else
	{
		if (std::stoi(server_response) == correct)
		{
			username = user_credentials.at(0);
			LoginData::username = user_credentials.at(0);
			LoginData::password = user_credentials.at(1);
			return true;
		}

		MessageBoxA(0, METASTRING("Error: Fatal error occured."), "", 0);
	}
	VM_SHARK_BLACK_END
	return false;
}