// Таблицы - базовый класс объектов-значений для сбалансированных деревьев

#ifndef __BALNODE_H
#define __BALNODE_H

#include <iostream>
#include "treenode.h"

#define BalOK     0
#define BalLeft  -1
#define BalRight  1

class TBalanceNode : public TTreeNode {
protected:
	int Balance; // индекс балансировки вершины (-1,0,1)
public:
	TBalanceNode(TKey k = "", PTDatValue pVal = NULL,
		PTTreeNode pL = NULL, PTTreeNode pR = NULL, int bal = BalOK) :
		TTreeNode(k, pVal, pL, pR), Balance(bal) {}
	virtual TDatValue *GetCopy(); // изготовить копию
	int  GetBalance(void) const { return Balance; }
	void SetBalance(int bal)    { Balance = bal; }
protected:
	virtual void Print(ostream &os) {
		TTreeNode::Print(os);
		os << " " << Balance;
	}
	friend class TBalanceTree;
};

typedef TBalanceNode *PTBalanceNode;

#endif
// end of balnode.h
