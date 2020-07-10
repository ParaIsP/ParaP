#pragma once
#include "pch.h"
#include <cstdint>

namespace Settings {
	extern bool bMenu;

	/* ESP SETTINGS */
	extern bool bESPEnable;
	extern bool bESPVisible;
	extern bool bESPTeam;
	extern bool bESPEnemy;
	extern bool bESPBoxes;
	extern bool bESPBoxesFilled;
	extern bool bESPHead;
	extern bool bESPDistance;
	extern bool bESPSnapline;
	extern bool bOutlineESP;
	extern bool bCavESP;
	extern bool bSkeletonESP;
	extern bool bESPHealth;
	extern float fESPHeadColor[4];
	extern float fESPHeadColorTeam[4];
	extern float fESPBoxColor[4];
	extern float fESPBoxColorTeam[4];
	extern float fESPSnaplinesColor[4];
	extern float fESPBoxesThickness;
	extern float fESPFillOpacity;

	extern bool aimKey[8];

	extern bool bPrepPhase;
	/* END ESP SETTINGS */

	extern int iSpeed;
	extern int droneAmmo;
	extern int droneDamage;
	/* AIMBOT */
	extern bool bAntiAim;
	extern bool bSilentAim;
	extern bool bAimbotEnabled;

	extern bool bNoRecoil;
	extern bool bNoSpread;
	extern bool bShootRun;
	extern bool bTeleport;

	extern bool bTeleKill;

	extern bool bDrawFOV;
	extern int iAimbotKey;
	extern int aimDist;
	extern int aimFov;
	extern int teleportTarget;
	extern int aimSmooth;
	extern uint64_t aimbotTarget;

	extern int damageModifier;
}

namespace GlowSettings
{
	extern bool bGlowEnable;
	extern float fGlowColor[4];
	extern float fGlowDistance;
	extern float fGlowOpacity;
}