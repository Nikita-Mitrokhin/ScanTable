// ������� - ������� (�����������) ����� ��������-�������� ��� ��������

#ifndef __TREENODE_H
#define __TREENODE_H

#include <iostream>
#include "trecord.h"

class   TTreeNode;
typedef TTreeNode *PTTreeNode;

class TTreeNode : public TTabRecord {
protected:
	PTTreeNode pLeft, pRight; // ��������� �� ����������
public:
	TTreeNode(TKey k = "", PTDatValue pVal = NULL,
		PTTreeNode pL = NULL, PTTreeNode pR = NULL) :
		TTabRecord(k, pVal), pLeft(pL), pRight(pR) {}
	PTTreeNode  GetLeft(void) const { return pLeft; }
	PTTreeNode  GetRight(void) const { return pRight; }
	virtual  TDatValue * GetCopy(); // ���������� �����
	friend class TTreeTable;
	friend class TBalanceTree;
};
#endif
// end of treenode.h
