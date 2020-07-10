#include "AesCryptoHandler.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "../MetaStr.h"
#include "Base64.h"
#include <CkGlobal.h>
#include <algorithm>
#include <CkCrypt2.h>
#include <CkByteData.h>

#pragma comment(lib, "chilkat/libs/ChilkatRel_x64.lib")

namespace AesCryptoHandler {
	void dump(const char* data, int len)
	{
		for (int i = 0; i < len; i++)
		{
			printf("%02X", (unsigned char)data[i]);
		}
		printf("\n");
	}


	std::string toString(const char* data, int len)
	{
		std::string buffAsStdStr;
		for (int i = 0; i < len; i++)
		{
			char buff[100];
			snprintf(buff, sizeof(100), "%02X", (unsigned char)data[i]);
			buffAsStdStr += buff;
		}
		return buffAsStdStr;
	}

	std::string random_string(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}


	std::string aes_decrypt(char* encryptedData, int size)
	{
		CkGlobal glob;
		glob.UnlockBundle("hello");

		CkCrypt2 decrypt;
		decrypt.put_CryptAlgorithm(METASTRING("aes"));
		decrypt.put_CipherMode(METASTRING("cbc"));
		decrypt.put_PaddingScheme(0);
		decrypt.put_EncodingMode(METASTRING("base64"));
		decrypt.SetEncodedIV(METASTRING("thcgg98726543210"), METASTRING("quoted-printable"));
		decrypt.SetEncodedKey(METASTRING("haddohaddohaddohaddohaddohaddoas"), METASTRING("quoted-printable"));



		const char* decStr = decrypt.decryptStringENC(encryptedData);
		return std::string(decStr);
	}


	std::string encrypt(std::string string_encrypt, std::string string_key)
	{
		CkGlobal glob;
		glob.UnlockBundle(random_string(500).c_str());

		CkCrypt2 crypt;
		crypt.put_CryptAlgorithm(METASTRING("aes"));
		crypt.put_CipherMode(METASTRING("cbc"));
		crypt.put_PaddingScheme(0);
		crypt.put_KeyLength(32);
		crypt.put_EncodingMode(METASTRING("base64"));
		crypt.SetEncodedIV(METASTRING("thcgg98726543210"), METASTRING("quoted-printable"));
		crypt.SetEncodedKey(METASTRING("haddohaddohaddohaddohaddohaddoas"), METASTRING("quoted-printable"));

		const char* decStr = crypt.encryptStringENC(string_encrypt.c_str());
		return std::string(decStr);
	}

	const unsigned char* decryptBytes(char* encryptedBytes, int size) {
		CkGlobal glob;
		glob.UnlockBundle("hello");

		CkCrypt2 decrypt;
		decrypt.put_CryptAlgorithm(METASTRING("aes"));
		decrypt.put_CipherMode(METASTRING("cbc"));
		decrypt.put_PaddingScheme(0);
		decrypt.put_EncodingMode(METASTRING("base64"));
		decrypt.SetEncodedIV(METASTRING("thcgg98726543210"), METASTRING("quoted-printable"));
		decrypt.SetEncodedKey(METASTRING("haddohaddohaddohaddohaddohaddoas"), METASTRING("quoted-printable"));

		CkByteData* pObj = new CkByteData();

		for (int i = 0; i < size; i++) {
			pObj->appendChar(encryptedBytes[i]);
		}

		CkByteData* decryptedData = new CkByteData();
		decrypt.DecryptBytes(*pObj, *decryptedData);

		return decryptedData->getBytes();
	}

	std::string get_encrypt_key(std::string username, std::string password)
	{
		std::string key = username;
		key.append(password);
		while (key.size() < 16)
		{
			key.append("#");
		}
		return key;
	}
}