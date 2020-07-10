#pragma once
#include <string>
#include <vector>

class paralyze_auth
{
public:
	paralyze_auth();
	~paralyze_auth();

	int check_login(std::string cheat);
	std::vector<std::string> get_credentials();

	std::string username;
	bool loginOk;

private:
	bool logged_in;
};

