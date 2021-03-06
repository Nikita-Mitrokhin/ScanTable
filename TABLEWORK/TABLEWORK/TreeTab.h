// ����, ���, ���� "������ ����������������-2", �++, ���
//
// treetab.h - Copyright (c) ������� �.�. 04.09.2000
//
// ������� �� ���������� �������� � ���� �������� ������

#ifndef __TREETAB_H
#define __TREETAB_H

#include <stack>
#include "ttable.h"
#include "treenode.h"

class TTreeTable : public TTable {
protected:
	PTTreeNode  pRoot;    // ��������� �� ������ ������
	PTTreeNode *ppRef;    // ����� ��������� �� �������-���������� � FindRecord
	PTTreeNode  pCurrent; // ��������� �� ������� �������
	int CurrPos;          // ����� ������� �������
	stack<PTTreeNode> St; // ���� ��� ���������
	void PrintTreeTab(ostream &os, PTTreeNode pNode); // ������
	void DrawTreeTab(PTTreeNode pNode, int Level);   // ������ � �������
	void DeleteTreeTab(PTTreeNode pNode);              // ��������
public:
	TTreeTable() : TTable() { CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot); }
	// �������������� ������
	virtual int IsFull() const;               // ��������� ?
	// �������� ������
	virtual PTDatValue FindRecord(TKey k); // ����� ������
	virtual void       InsRecord(TKey k, PTDatValue pVal); // ��������
	virtual void       DelRecord(TKey k); // ������� ������
	// ���������
	virtual TKey GetKey(void) const;        // ���� ������� ������
	virtual PTDatValue GetValuePtr(void) const; // ��������� �� ��������
	virtual int Reset(void);          // ���������� �� ������ ������
	virtual int IsTabEnded(void) const;    // ������� ��������� ?
	virtual int GoNext(void);          // ������� � ��������� ������
	// (=1 ����� ���������� GoNext ��� ��������� ������ �������)
	// ������ �������
	friend ostream& operator<<(ostream &os, TTreeTable &tab);
	void Draw(void); // ������ ������ (������� ����� �������)
	void Show(void); // ������ ������ (������� ������ ����)
protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTTreeNode pNode, int Level); // ��������� ����� lkz Show
};
#endif