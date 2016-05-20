// Сбалансироанные деревьев поиска (AVL-деревья)

#ifndef __BALTREE_H
#define __BALTREE_H

#include "treetab.h"
#include "balnode.h"

#define HeightOK  0
#define HeightInc 1

class TBalanceTree : public TTreeTable {
protected:  // вставить запись с балансировкой
	int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
	int LeftTreeBalancing(PTBalanceNode &pNode); // балансировка левого поодерева
	int RightTreeBalancing(PTBalanceNode &pNode); // балансировка правого поодерева
public:
	TBalanceTree() : TTreeTable() {}
	// основные методы
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить запись
	//  virtual void DelRecord ( TKey k );                  // удалить запись
};
#endif
