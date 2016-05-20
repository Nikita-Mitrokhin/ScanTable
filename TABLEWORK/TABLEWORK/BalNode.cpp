#include "stdafx.h"
#include "BalNode.h"
#include "treenode.h"

TDatValue * TBalanceNode::GetCopy()
{
	TBalanceNode *tmp = new TBalanceNode(Key, pValue, NULL, NULL, BalOK);
	return tmp;
}


// end of balnode.cpp
