// ��������������� �������� ������ (AVL-�������)

#ifndef __BALTREE_H
#define __BALTREE_H

#include "treetab.h"
#include "balnode.h"

#define HeightOK  0
#define HeightInc 1

class TBalanceTree : public TTreeTable {
protected:  // �������� ������ � �������������
	int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
	int LeftTreeBalancing(PTBalanceNode &pNode); // ������������ ������ ���������
	int RightTreeBalancing(PTBalanceNode &pNode); // ������������ ������� ���������
public:
	TBalanceTree() : TTreeTable() {}
	// �������� ������
	virtual void InsRecord(TKey k, PTDatValue pVal); // �������� ������
	//  virtual void DelRecord ( TKey k );                  // ������� ������
};
#endif
