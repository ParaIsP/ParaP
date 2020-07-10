#pragma once
#include <string>


namespace AesCryptoHandler {
	extern std::string decrypt(char* encryptedData, int size);
	extern std::string aes_decrypt(char* encryptedData, int size);
	extern std::string encrypt(std::string string_encrypt, std::string string_key);
	extern 	std::string get_encrypt_key(std::string username, std::string password);
	extern const unsigned char* decryptBytes(char* encryptedBytes, int size);
}