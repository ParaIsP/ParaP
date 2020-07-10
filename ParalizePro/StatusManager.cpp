#pragma once
#include "pch.h"
#include "CheatManager.h"
#include "Offsets.h"
#include <cstdint>

namespace StatusManager {

	int InGame() {
		uint64_t statusManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_ROUNDMANAGER);
		if (!statusManager) return 0;

		int state = pcm->rvm<int>(statusManager + 0x2E8);

		if (state == 2 || state == 3)
			return 1;

		return 0;
	}

	void setSpeed(int speed) {

	}
}