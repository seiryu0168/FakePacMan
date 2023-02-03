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
	csv.Load("map.csv");
	for (int z = 0; z < csv.GetHeight(); z++)
	{
		for (int x = 0; x < csv.GetWidth(); x++)
		{
			map[14-z][x] = -(csv.GetValue(z, x));
			if (map[14-z][x] == 0)
			{
				nodeMap_[14-z][x] = new Node(x, 14-z, STATUS::NONE);
			}
			else
				nodeMap_[14-z][x] = nullptr;
		}
	}
	int a[15][15] = {0};

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (nodeMap_[i][j])
				a[i][j] = 0;
			else
				a[i][j] = 1;
		}
	}

}

void AStarAI::SetPos(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	targetPos_ = targetPos;
	startPos_ = startPos;
}

void AStarAI::Calc(XMFLOAT3 targetPos, XMFLOAT3 startPos)
{
	ResetNode();
	SetPos(targetPos,startPos);
	//スタートノードのコスト計算
	int mCost = 0;
	int hCost = ((int)targetPos.x - (int)startPos.x) + ((14-(int)targetPos.z) - (14-(int)startPos.z));
	nodeMap_[(int)(14-startPos.z)][(int)startPos.x]->SetCost(mCost, hCost);
	
	//スタートノードが一番上の親なのでnullptr
	nodeMap_[(int)(14-startPos.z)][(int)startPos.x]->SetParent(nullptr);
	openNodeList_.push_back(nodeMap_[(int)(14-startPos.z)][(int)startPos.x]);
	Open(nodeMap_[(int)(14 - startPos.z)][(int)startPos.x]);
	Node* baseNode = *(openNodeList_.begin());
	while (true)
	{
		for (auto itr = openNodeList_.begin(); itr != openNodeList_.end(); itr++)
		{
			if (baseNode->GetScore() >= (*itr)->GetScore())
			{
				baseNode = (*itr);
			}
		}
		if (baseNode->GetStatus() != STATUS::CLOSE)
		{
			Open(baseNode);
			if (!openNodeList_.empty())
			{
				baseNode = *(openNodeList_.begin());
			}
		}
		else
			break;

	}

	GetPath();
}

void AStarAI::Open(Node* pN)
{
	//pNの上下左右のノードをopenする
	for (int i = 0; i < 4; i++)
	{
		int posX = (int)pN->GetPos().x + d[i].dirX;
		int posZ = (int)pN->GetPos().z + d[i].dirZ;

		//次の座標が壁じゃないなら
		if (map[posZ][posX] == 0 &&
			nodeMap_[posZ][posX]->GetStatus()==STATUS::NONE)
		{
			int mCost = pN->GetmCost() + 1;
			int hCost = abs((int)targetPos_.x - nodeMap_[posZ][posX]->GetPos().x) + abs((14-(int)targetPos_.z) - (nodeMap_[posZ][posX]->GetPos().z));
			nodeMap_[posZ][posX]->SetStatus(STATUS::OPEN);
			nodeMap_[posZ][posX]->SetCost(mCost, hCost);
			nodeMap_[posZ][posX]->SetParent(pN);
			openNodeList_.push_back(nodeMap_[posZ][posX]);
		}
	}
	for (auto itr = openNodeList_.begin(); itr != openNodeList_.end(); itr++)
	{
		if ((*itr) == pN)
		{
			itr = openNodeList_.erase(itr);
			break;
		}
	}

	pN->SetStatus(STATUS::CLOSE);
	closedNodeList_.push_back(pN);
}

void AStarAI::GetPath()
{
	Node* pathNode = nodeMap_[14 - (int)targetPos_.z][(int)targetPos_.x];
	while (true)
	{

		path_.push_back({(int)pathNode->GetPos().x, (int)pathNode->GetPos().z});
		if (pathNode == nodeMap_[14 - (int)startPos_.z][(int)startPos_.x])
			break;
		pathNode = pathNode->GetParent();

	}
}

void AStarAI::ResetNode()
{
	for (int z = 0; z < csv.GetHeight(); z++)
	{
		for (int x = 0; x < csv.GetWidth(); x++)
		{
			if (nodeMap_!=nullptr)
			{
				nodeMap_[z][x]->SetCost(0, 0);
				nodeMap_[z][x]->SetParent(nullptr);
				nodeMap_[z][x] = new Node(x, z, STATUS::NONE);
			}
			else
				nodeMap_[z][x] = nullptr;
		}
	}
	openNodeList_.clear();
	closedNodeList_.clear();
	path_.clear();
}
