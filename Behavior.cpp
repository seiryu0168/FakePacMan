#include "Behavior.h"

Behavior::Behavior()
	:vMove_(XMVectorSet(0,0,0,0)),
	modelName_("")
{
}

void Behavior::SetVector(XMVECTOR vec)
{
	vMove_ = vec;
}

float Behavior::CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	float a = sqrtf(powf((targetPos.x - startPos.x), 2) + powf((targetPos.z - startPos.z), 2));
	return a;
}