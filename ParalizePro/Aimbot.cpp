#pragma once
#include "StatusManager.h"
#include <cfloat>
#include "Settings.h"
#include <cstdint>
#include "LocalPlayerManager.h"
#include "Entity.h"
#include "CheatManager.h"
#include "Offsets.h"
#include "GameRenderer.h"
#include "ImGui/imgui.h"

constexpr float r2d = 57.2957795131f;
constexpr float d2r = 0.01745329251f;
#define PI 3.14159265358979323846f


namespace Aimbot {

	float W2SDistance(Vector3 position)
	{
		ImGuiIO& io = ImGui::GetIO();
		Vector3 v = GameRenderer::W2S(position);
		return (abs(v.x - (io.DisplaySize.x / 2)) + abs(v.y - (io.DisplaySize.y / 2)));
	}

	Vector3 VectorAngles(Vector3 forward)
	{
		Vector3 angles;
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.y == 0)
		{
			yaw = 0;
			if (forward.y > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = (float)(atan2(forward.y, forward.x) * 180 / PI);


			tmp = (float)sqrt(forward.x * forward.x + forward.y * forward.y);
			pitch = (float)(atan2(forward.z * -1, tmp) * 180 / PI);

		}

		yaw += 90;

		if (yaw > 180)
		{
			yaw -= 360;
		}
		if (pitch > 180)
		{
			pitch -= 360;
		}

		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0;
		return angles;
	}

	Vector3 ToEuler(Vector4 q)
	{
		Vector3 end = Vector3();

		float sinr = (float)(+2.0 * (q.w * q.x + q.y * q.z));
		float cosr = (float)(+1.0 - 2.0 * (q.x * q.x + q.y * q.y));
		end.z = (float)atan2(sinr, cosr);

		double sinp = +2.0 * (q.w * q.y - q.z * q.x);
		if (abs(sinp) >= 1)
			end.x = (float)copysign(PI / 2, sinp);
		else
			end.x = (float)asin(sinp);

		double siny = +2.0 * (q.w * q.z + q.x * q.y);
		double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
		end.y = (float)atan2(siny, cosy);

		return end;
	}

	float GetDifference(float firstAngle, float secondAngle)
	{
		float difference = secondAngle - firstAngle;
		while (difference < -180.f) difference += 360.f;
		while (difference > 180.f) difference -= 360.f;
		return difference;
	}

	Vector4 QuaternionFromYPR(float yaw, float pitch, float roll)
	{
		Vector4 q;
		double cy = cos(yaw * 0.5);
		double sy = sin(yaw * 0.5);
		double cr = cos(pitch * 0.5);
		double sr = sin(pitch * 0.5);
		double cp = cos(roll * 0.5);
		double sp = sin(roll * 0.5);

		q.w = (float)(cy * cr * cp + sy * sr * sp);
		q.x = (float)(cy * sr * cp - sy * cr * sp);
		q.y = (float)(cy * cr * sp + sy * sr * cp);
		q.z = (float)(sy * cr * cp - cy * sr * sp);
		return q;
	}

	Vector3 calc_angle(Vector3 enemy)
	{
		Vector3 dir = enemy - GameRenderer::GetTranslation();

		float x = asin(dir.z / dir.len(dir)) * r2d;
		float z = atan(dir.y / dir.x) * r2d;

		if (dir.x >= 0.f) z += 180.f;
		if (x > 179.99f) x -= 360.f;
		else if (x < -179.99f) x += 360.f;


		return Vector3(x, 0.f, z + 90.f);

	}




	void clamp(Vector3& angle)
	{
		if (angle.x > 75.f) angle.x = 75.f;
		else if (angle.x < -75.f) angle.x = -75.f;
		if (angle.z < -180) angle.z += 360;
		else if (angle.z > 180) angle.z -= 360;
		//angle.y = 0.f;
	}

	Vector4 CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		Vector4 result;

		float sr, cr, sp, cp, sy, cy;

		float halfRoll = roll * 0.5f;
		sr = sin(halfRoll);
		cr = cos(halfRoll);

		float halfPitch = pitch * 0.5f;
		sp = sin(halfPitch);
		cp = cos(halfPitch);

		float halfYaw = yaw * 0.5f;
		sy = sin(halfYaw);
		cy = cos(halfYaw);

		result.x = cy * sr * cp - sy * cr * sp;
		result.y = cy * cr * sp + sy * sr * cp;
		result.z = sy * cr * cp - cy * sr * sp;
		result.w = cy * cr * cp + sy * sr * sp;
		return result;
	}

	Vector4 GetAngle(Vector3 viewTranslation, Vector3 enemyHead, Vector4 originalAngle)
	{
		Vector3 aimAngle = VectorAngles(viewTranslation - enemyHead);
		Vector3 currentAngle = ToEuler(originalAngle);
		currentAngle *= (float)(180.f / PI);
		Vector3 currentAngleV = Vector3(currentAngle.z, currentAngle.y, currentAngle.x);

		Vector3 smoothedAngle = Vector3(aimAngle.x, aimAngle.y, aimAngle.z);
		smoothedAngle.x = GetDifference(currentAngleV.x, smoothedAngle.x);
		smoothedAngle.y = GetDifference(currentAngleV.y, smoothedAngle.y);
		smoothedAngle *= (Settings::aimSmooth * 0.01f);
		currentAngleV.x += smoothedAngle.x;
		currentAngleV.y += smoothedAngle.y;

		if (currentAngleV.x > 89.0f && currentAngleV.x <= 180.0f)
		{
			currentAngleV.x = 89.0f;
		}
		while (currentAngleV.x > 180.f)
		{
			currentAngleV.x -= 360.f;
		}
		while (currentAngleV.x < -89.0f)
		{
			currentAngleV.x = -89.0f;
		}
		while (currentAngleV.y > 180.f)
		{
			currentAngleV.y -= 360.f;
		}
		while (currentAngleV.y < -180.f)
		{
			currentAngleV.y += 360.f;
		}

		aimAngle *= (float)(PI / 180.f);
		currentAngle *= (float)(PI / 180.f);
		currentAngleV *= (float)(PI / 180.f);

		Vector4 newQuaternion = QuaternionFromYPR(currentAngleV.y, currentAngleV.x, 0);
		return newQuaternion;
	}

	bool getAimKey() {
		if (Settings::aimKey[2])
			return GetAsyncKeyState(VK_CAPITAL);
		if (Settings::aimKey[0])
			return GetAsyncKeyState(VK_LBUTTON);
		if (Settings::aimKey[1])
			return GetAsyncKeyState(VK_RBUTTON);
		if (Settings::aimKey[3])
			return GetAsyncKeyState(VK_MENU);
		if (Settings::aimKey[4])
			return GetAsyncKeyState(VK_SHIFT);
		if (Settings::aimKey[5])
			return GetAsyncKeyState(VK_XBUTTON1);
		if (Settings::aimKey[6])
			return GetAsyncKeyState(VK_XBUTTON2);
	}


	void normalAimbot() {
		uint64_t target = -1;

		float fBestDistanceFromCross = FLT_MAX;
		float fTargetDistance = FLT_MAX;

		uint64_t localPlayer = LocalPlayerManager::getLocalPlayer();
		Entity::setSilentViewAngles(localPlayer, Entity::getViewAngles(localPlayer));

		if (Settings::bAimbotEnabled){
			int localHealth = Entity::getHealth(localPlayer);
			int localTeam = Entity::getTeam(localPlayer);
			if (localHealth <= 0) return;

			uint64_t gameManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GAMEMANAGER);
			uint64_t entityList = pcm->rvm<uint64_t>(gameManager + 0x1C8);

			for (int i = 0; i <= 10; i++) {
				uint64_t entity = pcm->rvm<uint64_t>(entityList + i * 0x8);
				int entityHealth = Entity::getHealth(entity);
				int entityTeam = Entity::getTeam(entity);

				if (entityHealth > 0 && entityTeam != localTeam) {
					auto vCurrentEntityHeadPos = Entity::getHead(entity);
					auto vCurrentEntityWSPos = GameRenderer::W2S(vCurrentEntityHeadPos);
					auto vCurrentEntityPos = Entity::getPosition(entity);
					auto vCurrentLocalPos = Entity::getPosition(localPlayer);
					auto fCurrentDistanceFromCross = W2SDistance(vCurrentEntityHeadPos);
					auto fCurrentDistance = GameRenderer::GetTranslation().Distance(vCurrentEntityHeadPos);
					auto fzDifference = vCurrentLocalPos.z - vCurrentEntityPos.z;
					auto fDistance = vCurrentLocalPos.Distance(vCurrentEntityPos);

					if (fDistance < Settings::aimDist)
					{
						if (fCurrentDistanceFromCross <= Settings::aimFov && fCurrentDistanceFromCross >= -(Settings::aimFov) && vCurrentEntityWSPos.z >= 1.f)
						{
							if (vCurrentEntityHeadPos.y > 1 || vCurrentEntityHeadPos.y < -1)
							{
								if (fCurrentDistanceFromCross < fBestDistanceFromCross)
								{

									fBestDistanceFromCross = fCurrentDistanceFromCross;
									target = entity;
								}
							}
						}
					}
				}
			}

			if (target != -1) {
				Vector3 headPos = Entity::getHead(target);
				if (getAimKey()) {
					Vector3 angles = calc_angle(headPos);
					clamp(angles);
					Vector4 stuff = CreateFromYawPitchRoll(angles.z * d2r, 0, angles.x * d2r);
					Entity::setViewAngles(LocalPlayerManager::getLocalPlayer(), stuff);
				}

				Settings::aimbotTarget = target;
				fTargetDistance = FLT_MAX;
				fBestDistanceFromCross = FLT_MAX;
				target = NULL;
			}
		}
	}

	void silentAimbot() {
		uint64_t target = -1;

		float fBestDistanceFromCross = FLT_MAX;
		float fTargetDistance = FLT_MAX;

		uint64_t localPlayer = LocalPlayerManager::getLocalPlayer();
		if (!localPlayer) return;
		Entity::setSilentViewAngles(localPlayer, Entity::getViewAngles(localPlayer));

		if (Settings::bAimbotEnabled) {
			int localHealth = Entity::getHealth(localPlayer);
			int localTeam = Entity::getTeam(localPlayer);
			if (localHealth <= 0) return;

			uint64_t gameManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GAMEMANAGER);
			uint64_t entityList = pcm->rvm<uint64_t>(gameManager + 0x1C8);

			for (int i = 0; i <= 10; i++) {
				uint64_t entity = pcm->rvm<uint64_t>(entityList + i * 0x8);
				int entityHealth = Entity::getHealth(entity);
				int entityTeam =  Entity::getTeam(entity);

				if (entityHealth > 0 && entityTeam != localTeam) {
					auto vCurrentEntityHeadPos = Entity::getHead(entity);
					auto vCurrentEntityWSPos = GameRenderer::W2S(vCurrentEntityHeadPos);
					auto vCurrentEntityPos = Entity::getPosition(entity);
					auto vCurrentLocalPos = Entity::getPosition(localPlayer);
					auto fCurrentDistanceFromCross = W2SDistance(vCurrentEntityHeadPos);
					auto fCurrentDistance = GameRenderer::GetTranslation().Distance(vCurrentEntityHeadPos);
					auto fzDifference = vCurrentLocalPos.z - vCurrentEntityPos.z;
					auto fDistance = vCurrentLocalPos.Distance(vCurrentEntityPos);

					if (fDistance < Settings::aimDist)
					{
						if (fCurrentDistanceFromCross <= Settings::aimFov && fCurrentDistanceFromCross >= -(Settings::aimFov) && vCurrentEntityWSPos.z >= 1.f)
						{
							if (vCurrentEntityHeadPos.y > 1 || vCurrentEntityHeadPos.y < -1)
							{
								if (fCurrentDistanceFromCross < fBestDistanceFromCross)
								{

									fBestDistanceFromCross = fCurrentDistanceFromCross;
									target = entity;
								}
							}
						}
					}
				}
			}

			if (target != -1) {
				Vector3 headPos = Entity::getHead(target);
				Vector3 angles = calc_angle(headPos);
				clamp(angles);
				Vector4 stuff = CreateFromYawPitchRoll(angles.z * d2r, 0, angles.x * d2r);

				if (getAimKey()) {
					Entity::setSilentViewAngles(LocalPlayerManager::getLocalPlayer(), stuff);
				}
				else {
					Entity::setSilentViewAngles(localPlayer, Entity::getViewAngles(localPlayer));
				}

				Settings::aimbotTarget = target;
				fTargetDistance = FLT_MAX;
				fBestDistanceFromCross = FLT_MAX;
				target = NULL;
			}
		}
	}

	void entryThread() {
		Sleep(2500);

		while (true) {
			if (!StatusManager::InGame()) continue;

			if (!Settings::bSilentAim)
				normalAimbot();
			else
				silentAimbot();

			Sleep(1);
		}
	}
}