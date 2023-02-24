#pragma once
#include"player.h"
#include"AStarAI.h"

class Behavior
{
private:
	XMVECTOR vMove_;
	std::string modelName_;
public:
	Behavior();
	virtual void Update() {};
	 void SetVector(XMVECTOR vec);
	 XMVECTOR GetVector() { return vMove_; };
	 virtual void SetModelName(std::string name) { modelName_ = name; }
	 std::string GetModelName() { return modelName_; }
	float CulcDistance(XMFLOAT3 targetPos, XMFLOAT3 startPos);
};

