#pragma once
#include"Engine/Direct3D.h"
enum class STATUS
{
	NONE = 0,
	OPEN,
	CLOSE,
};

class Node
{
private:

	int mCost_;
	int hCost_;

	int score_;

	int X_;
	int Z_;

	STATUS status_;
	Node* pParentNode_;
public:
	Node();
	Node(int posX, int posZ,STATUS st);
	~Node();

	void SetPos(int posX, int posZ);
	void SetParent(Node* parent);
	void SetCost(int mCost,int hCost);
	void SetStatus(STATUS st);
	int GetScore() { return score_; }
	XMFLOAT3 GetPos() { return XMFLOAT3(X_, 0, Z_); }
	int GetmCost() { return mCost_; }
	int GethCost() { return hCost_; }
	STATUS GetStatus() { return status_; }
	Node* GetParent();
};

