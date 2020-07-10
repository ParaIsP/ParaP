#pragma once
#include <chrono>

class paralyze_security
{
public:
	paralyze_security();
	~paralyze_security();

	void start_security_thread();
	bool securityOk;
	std::chrono::steady_clock::time_point security_time;
	
};

