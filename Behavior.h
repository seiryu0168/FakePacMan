#pragma once
#include"player.h"
#include"AStarAI.h"

class Behavior
{
private:
	XMVECTOR vMove_;
public:
	Behavior();
	virtual void Update() {};
	 void SetVector(XMVECTOR vec);
	 XMVECTOR GetVector() { return vMove_; };
	//virtual void SearchMode() {};
	float CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos);
};

