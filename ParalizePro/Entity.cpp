#pragma once
#include <cstdint>
#include "CheatManager.h"
#include "Offsets.h"

namespace Entity {

	Vector3 getPosition(uint64_t entity) {
		uint64_t entSkeleton = pcm->rvm<uint64_t>(entity + OFFSET_ENTITY_SKELETON);
		if (!entSkeleton) return Vector3(0, 0, 0);
		return pcm->rvm <Vector3>(entSkeleton + OFFSET_SKELETON_POSITION);
	}

	Vector3 getHead(uint64_t entity) {
		uint64_t entSkeleton = pcm->rvm<uint64_t>(entity + OFFSET_ENTITY_SKELETON);
		if (!entSkeleton) return Vector3(0, 0, 0);
		return pcm->rvm<Vector3>(entSkeleton + OFFSET_SKELETON_HEAD);
	}

	int getHealth(uint64_t entity) {
		uint64_t entityInfo = pcm->rvm<uint64_t>(entity + OFFSET_ENTITY_ENTITYINFO);
		if (!entityInfo) return 0;
		uint64_t pMainComponent = pcm->rvm<uint64_t>(entityInfo + OFFSET_ENTITYINFO_MAINCOMPONENT);
		if (!pMainComponent) return 0;
		uint64_t pChildComponent = pcm->rvm<uint64_t>(pMainComponent + OFFSET_MAINCOMPONENT_CHILDCOMPONENT);
		if (!pChildComponent) return 0;

		return pcm->rvm<int>(pChildComponent + OFFSET_CHILDCOMPONENT_HEALTH);
	}

	int getTeam(uint64_t entity) {
		uint64_t playerInfo = pcm->rvm<uint64_t>(entity + OFFSET_ENTITY_REPLICATION);
		if (!playerInfo) return 0;
		return pcm->rvm<int>(playerInfo + OFFSET_ENTITY_REPLICATION_TEAM);
	}

	void setViewAngles(uint64_t entity, Vector4 angles) {
		uint64_t view = pcm->rvm<uint64_t>(entity + 0x20);
		if (!view) return;
		view = pcm->rvm<uint64_t>(view + 0x11A0);
		if (!view) return;
		pcm->wvm<Vector4>(view + 0xC0, angles);
	}

	Vector4 getViewAngles(uint64_t entity) {
		uint64_t view = pcm->rvm<uint64_t>(entity + 0x20);
		if (!view) return Vector4(0,0,0,0);
		view = pcm->rvm<uint64_t>(view + 0x11A0);
		if (!view) return Vector4(0, 0, 0, 0);
		return pcm->rvm<Vector4>(view + 0xC0);
	}


	void setSilentViewAngles(uint64_t entity, Vector4 angles) {
		uint64_t view = pcm->rvm<uint64_t>(entity + 0x20);
		if (!view) return;
		view = pcm->rvm<uint64_t>(view + 0x11A0);
		if (!view) return;
		pcm->wvm<Vector4>(view + 0x134, angles);
	}

	Vector4 getSilentViewAngles(uint64_t entity) {
		uint64_t view = pcm->rvm<uint64_t>(entity + 0x20);
		if (!view) return Vector4(0, 0, 0, 0);
		view = pcm->rvm<uint64_t>(view + 0x11A0);
		if (!view) return Vector4(0, 0, 0, 0);
		return pcm->rvm<Vector4>(view + 0x134);
	}

	void setSpeed(uint64_t entity, int speed) {
		uint64_t speedPtr = pcm->rvm < uint64_t >(entity + 0x30);
		if (!speedPtr) return;
		speedPtr = pcm->rvm < uint64_t >(speedPtr + 0x30);
		if (!speedPtr) return;
		speedPtr = pcm->rvm < uint64_t >(speedPtr + 0x38);
		if (!speedPtr) return;

		pcm->wvm<int>(speedPtr + 0x58, speed);
	}

	void enableCav(uint64_t entity, int enable) {
		return;

		for (int a = 0; a < 6; a++) {
			uint64_t cavO = pcm->rvm<uint64_t>(entity + 0x20);
			cavO = pcm->rvm<uint64_t>(cavO + 0x18);
			cavO = pcm->rvm<uint64_t>(cavO + 0xD8);
			cavO = pcm->rvm<uint64_t>(cavO + (uintptr_t)0x78 + (a * 0x8));

			int check = pcm->rvm<int>(cavO + 0x531);
			if (!check) continue;

			pcm->wvm<int>(cavO + 0x532, enable);
			pcm->wvm<int>(cavO + 0x534, enable);
		}
	}
}