#include "./sha1.h"

namespace sha1crypto {

int SHA1::getCipherLen(int len)
{
    return 20;
}


void SHA1::reset()
{
    sha1.Restart();
}

void SHA1::update(const char * indata, int len)
{
    sha1.Update((const unsigned char *)indata, len);
}

int SHA1::final(char * outdata)
{
    sha1.Final((unsigned char *)outdata);
    return 20;
}

int SHA1::digest(const char * indata, int len, char * outdata)
{
    sha1.CalculateDigest((unsigned char *)outdata, (const unsigned char *)indata, len);
    return 20;
}

std::string SHA1::to_string(const char * data, int len)
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

std::string SHA1::get_sha1(std::string instr) {
	SHA1 sha1;
	const char * indata = instr.c_str();
	int inlen = (int)strlen(indata);
	char * outdata = new char[sha1.getCipherLen(inlen)];
	int outlen = sha1.digest(indata, inlen, outdata);
	return to_string(outdata, outlen);
}
}

