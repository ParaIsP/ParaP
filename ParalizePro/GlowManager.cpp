#pragma once
#include "pch.h"
#include "CheatManager.h"
#include "Offsets.h"
#include <cstdint>
#include "Settings.h"

namespace GlowManager {

	void doGlow() {
		uint64_t glowManager = pcm->rvm<uint64_t>(pcm->r6base + ADDRESS_GLOWBASE);
		if (!glowManager) return;

		glowManager = pcm->rvm<uint64_t>(glowManager + 0xB8);


		if (GlowSettings::bGlowEnable) {
			float r = GlowSettings::fGlowColor[0] * 255;
			float g = GlowSettings::fGlowColor[1] * 255;
			float b = GlowSettings::fGlowColor[2] * 255;

			pcm->wvm<float>(glowManager + 0x0110, r); // r
			pcm->wvm<float>(glowManager + 0x0114, g); // g
			pcm->wvm<float>(glowManager + 0x0118, b); // b

			float alpha = 0;
			pcm->wvm<float>(glowManager + 0x0138, alpha); // alpha


			float opacity = 0;
			pcm->wvm<float>(glowManager + 0x013C, opacity); // opacity
		}
		else {
			float r = 0;
			float g = 0;
			float b = 0;

			pcm->wvm<float>(glowManager + 0x0110, r); // r
			pcm->wvm<float>(glowManager + 0x0114, g); // g
			pcm->wvm<float>(glowManager + 0x0118, b); // b

			float alpha = 500;
			pcm->wvm<float>(glowManager + 0x0138, alpha); // alpha


			float opacity = 0;
			pcm->wvm<float>(glowManager + 0x013C, opacity); // opacity
		}
	}
}