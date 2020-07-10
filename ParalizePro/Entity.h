#pragma once
#include <cstdint>
#include "Vectors.h"

namespace Entity {
		extern Vector3 getPosition(uint64_t entity);
		extern Vector3 getHead(uint64_t entity);
		extern int getHealth(uint64_t entity);
		extern int getTeam(uint64_t entity);
		extern void setViewAngles(uint64_t entity, Vector4 angles);
		extern Vector4 getViewAngles(uint64_t entity);
		extern void setSilentViewAngles(uint64_t entity, Vector4 angles);
		extern Vector4 getSilentViewAngles(uint64_t entity);
		extern void setSpeed(uint64_t entity, int speed);
		extern void enableCav(uint64_t entity, int enable);
}