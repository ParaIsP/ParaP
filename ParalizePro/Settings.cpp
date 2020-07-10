#pragma once
#include <cstdint>
namespace Settings {
	bool bMenu = false;


	/* ESP SETTINGS */
	bool bESPEnable = true;
	bool bESPVisible = false;
	bool bESPBoxes = true;
	bool bESPBoxesFilled = true;
	bool bESPHead = true;
	bool bESPTeam = false;
	bool bESPEnemy = true;
	bool bESPHealth = true;
	bool bESPDistance = false;
	bool bESPSnapline = false;
	bool bOutlineESP = false;
	bool bCavESP = false;
	bool bSkeletonESP = false;
	float fESPHeadColor[4] = { 1.f, 0.f, 0.f, 255.f };
	float fESPHeadColorTeam[4] = { 0.f, 1.f, 0.f, 255.f };
	float fESPBoxColor[4] = { 1.f, 0.f, 0.f, 255.f };
	float fESPBoxColorTeam[4] = { 0.f, 1.f, 0.f, 255.f };
	float fESPSnaplinesColor[4];
	float fESPBoxesThickness = 1.0f;
	float fESPFillOpacity = 120.f;
	/* END ESP SETTINGS */

	int iSpeed = 105;


	bool bTeleKill = false;
	bool bPrepPhase = false;

	bool bNoRecoil = true;
	bool bNoSpread = true;
	bool bShootRun = true;
	bool bTeleport = true;

	/* AIMBOT */

	int damageModifier = 1;
	int droneAmmo = 5;
	int droneDamage = 10;


	bool bAntiAim = false;
	bool bSilentAim = false;
	bool bAimbotEnabled = true;
	bool bDrawFOV = false;
	int iAimbotKey = 0;

	bool aimKey[8] = { true, false, false, false, false, false, false, false };

	int aimFov = 720;
	int aimDist = 300;
	uint64_t aimbotTarget = -1;
	int teleportTarget = -1;
	int aimSmooth = 0;
}

namespace GlowSettings
{
	bool bGlowEnable = false;
	float fGlowColor[4] = { 0.5372549295f, 0.5372549295, 1.f, 1.f };
	float fGlowDistance = 50;
	float fGlowOpacity = 0;
}