#pragma once
#include"player.h"
#include"AStarAI.h"

class Behavior
{
private:
public:
	Behavior();
	virtual void Update() {};
	//virtual void ChaseMode() {};
	//virtual void SearchMode() {};
	float CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos);
};

