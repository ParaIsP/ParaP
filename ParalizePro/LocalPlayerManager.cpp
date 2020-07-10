#pragma once
#include <cstdint>
#include "CheatManager.h"
#include "Offsets.h"

namespace LocalPlayerManager {

	uint64_t getLocalPlayer() {
		uint64_t interfaceManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_INTERFACEMANAGER);
		if (!interfaceManager) return 0;
		uint64_t LocalPlayer = pcm->rvm<uint64_t>(interfaceManager + 0x68);
		if (!LocalPlayer) return 0;
		LocalPlayer = pcm->rvm<uint64_t>(LocalPlayer + 0x0);
		if (!LocalPlayer) return 0;

		return pcm->rvm<uint64_t>(LocalPlayer + 0x28);
	}
}