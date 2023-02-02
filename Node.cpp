#include "Node.h"

Node::Node()
	:mCost_(0),
	 hCost_(0),
	 score_(0),
	X_(0),
	Z_(0),
	status_(STATUS::NONE),
	pParentNode_(nullptr)
{
}

Node::Node(int posX, int posZ,STATUS st)
	:mCost_(0),
 	 hCost_(0),
	 score_(0),
	 X_(posX),
	 Z_(posZ),
	 status_(st),
	 pParentNode_(nullptr)
{
}

Node::~Node()
{
}

void Node::SetPos(int posX, int posZ)
{
	X_ = posX;
	Z_ = posZ;
}

void Node::SetParent(Node* parent)
{
	pParentNode_ = parent;
}

void Node::SetCost(int mCost, int hCost)
{
	mCost_ = mCost;
	hCost_ = hCost;
	score_ = mCost_ + hCost_;
}

void Node::SetStatus(STATUS st)
{
	status_ = st;
}
