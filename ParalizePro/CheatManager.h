#pragma once
#include <string>
#include "paralyze_cheat_memory.h"
#include <vector>
#include "Security/paralyze_security.h"
#include "Drawing/paralyze_drawing.h"
#include "Vectors.h"

#define PCD(x) (std::cout << x << std::endl) 
#define PCDH(x) (std::cout << std::hex << x << std::dec << std::endl) 

extern paralyze_cheat_memory* pcm;
extern paralyze_security* pcs;
extern paralyze_drawing* pcd;


namespace Global
{
	extern bool bMenu;
	extern std::string cheat_username;
	extern int monitorX;
	extern int monitorY;
}



