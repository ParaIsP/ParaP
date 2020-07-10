#include "CheatManager.h"
#include <vector>
#include <sstream>
#include <lmcons.h>
#include <fstream>
#include <Tlhelp32.h>
#include "Security/paralyze_security.h"
#include "Drawing/paralyze_drawing.h"

paralyze_cheat_memory* pcm;
paralyze_drawing* pcd;

namespace Global
{
	bool bMenu = 1;
	std::string cheat_username = "";
	int monitorX = 0;
	int monitorY = 0;
}

