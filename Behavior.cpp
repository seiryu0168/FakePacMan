#include "Behavior.h"

float Behavior::CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	float a = sqrtf(powf((targetPos.x - startPos.x), 2) + powf((targetPos.z - startPos.z), 2));
	return a;
}