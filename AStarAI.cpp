#include "AStarAI.h"
#include"Engine/CsvReader.h"

AStarAI::AStarAI()	 
{
}

AStarAI::~AStarAI()
{
}

void AStarAI::Init()
{
	CsvReader csv;
	csv.Load("map.csv");
	for (int z = 0; z < csv.GetHeight(); z++)
	{
		for (int x = 0; x < csv.GetWidth(); x++)
		{
			map[z][x] = csv.GetValue(z, x);
		}
	}

}

void AStarAI::Update()
{
}

void AStarAI::SetPos(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	targetPos_ = targetPos;
}

void AStarAI::Calc(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	int mCost = 0;
	int hCost = (targetPos.x - startPos.x) + (targetPos.z - startPos.z);
	Node* pNode = new Node(startPos.x, startPos.z, STATUS::OPEN);
	
	pNode->SetCost(mCost, hCost);
	pNode->SetParent(nullptr);
	while (true)
	{

	}
}

void AStarAI::Open(Node* pN)
{
	for (int i = 0; i < 4; i++)
	{
		Node* pNode = new Node(pN->GetPos().x + d[i].dirX, pN->GetPos().z + d[i].dirZ, STATUS::OPEN);
		int mCost = pN->GetmCost()+1;
		int hCost = (targetPos_.x - pNode->GetPos().x) + (targetPos_.z - pNode->GetPos().z);
		pNode->SetCost(mCost, hCost);
		pNode->SetParent(pN);
		openNodeList_.push_back(pNode);

	}
	pN->SetStatus(STATUS::CLOSE);
	closedNodeList_.push_back(pN);
}
