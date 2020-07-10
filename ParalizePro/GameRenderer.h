#pragma once
#include "pch.h"
#include "Vectors.h"

namespace GameRenderer {
	extern Vector3 GetEntityBone(DWORD_PTR Entity, __int64 BoneID);
	extern Vector3 W2S(Vector3 position);
	extern Vector3 GetTranslation();
}