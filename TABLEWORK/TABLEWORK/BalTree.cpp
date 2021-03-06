// ��������������� �������� ������ (AVL-�������)
#include "stdafx.h"
#include "BalTree.h"
#include <math.h>
#include <conio.h>


void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) { // �������� ������
	if (IsFull()) SetRetCode(TabFull);
	else InsBalanceTree((PTBalanceNode&)pRoot, k, pVal);
}           

// �������� ������ - ������������
int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal) {
	int HeighIndex = HeightOK;
	if (pNode == NULL) { // ������� �������
		SetRetCode(TabOK);
		pNode = new TBalanceNode(k, pVal);
		HeighIndex = HeightInc;
		DataCount++;
	}
	else if (k < pNode->GetKey()) {
		if (InsBalanceTree((PTBalanceNode&)(pNode->pLeft), k, pVal) == HeightInc)
			// ����� ������� ������ ������ ��������� ����������� - ������������
			HeighIndex = LeftTreeBalancing(pNode);
	}
	else   if (k > pNode->GetKey()) {
		if (InsBalanceTree((PTBalanceNode&)(pNode->pRight), k, pVal) == HeightInc)
			// ����� ������� ������ ������� ��������� ����������� - ������������
			HeighIndex = RightTreeBalancing(pNode);
	}
	else { // ���������� ������
		SetRetCode(TabRecDbl);
		HeighIndex = HeightOK;
	}
	return HeighIndex;
}           

// ������������ ����� ������� � ����� ���������
int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch (pNode->GetBalance()) { // �������� ���������� ������������
	case BalRight: pNode->SetBalance(BalOK);  // � ��������� ��� ������� ������
		HeighIndex = HeightOK; break;        // �������������� ����������
	case BalOK:    pNode->SetBalance(BalLeft);// � ��������� ���� ����������
		HeighIndex = HeightInc; break;       // �������������� ������� �����
	case BalLeft: // � ��������� ��� ������� ����� - ���������� ������������
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->pLeft);
		if (p1->GetBalance() == BalLeft) { // ������ 1 - ����������� LL-�������
			pNode->pLeft = p1->pRight; // 1
			p1->pRight = pNode;      // 2
			pNode->SetBalance(BalOK);  // 3
			pNode = p1;
		}
		else { // ������ 2 - ���������� LR-�������
			p2 = PTBalanceNode(p1->pRight);
			p1->pRight = p2->pLeft;  // 1
			p2->pLeft = p1;         // 2
			pNode->pLeft = p2->pRight; // 3
			p2->pRight = pNode;      // 4
			if (p2->GetBalance() == BalLeft) pNode->SetBalance(BalRight);
			else pNode->SetBalance(BalOK); // 5
			if (p2->GetBalance() == BalRight) p1->SetBalance(BalLeft);
			else p1->SetBalance(BalOK);    // 6
			pNode = p2;
		}
		pNode->SetBalance(BalOK);
		HeighIndex = HeightOK;
	}
	return HeighIndex;
}            

// ������������ ����� ������� � ������ ���������
int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch (pNode->GetBalance()) {
	case BalLeft:
		pNode->SetBalance(BalOK);
		HeighIndex = HeightOK;
		break;
	case BalOK:
		pNode->SetBalance(BalRight);
		HeighIndex = HeightInc;
		break;
	case BalRight:
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->GetRight());
		if (p1->GetBalance() == BalRight) {
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->SetBalance(BalOK);
			pNode = p1;

		}
		else {
			p2 = PTBalanceNode(p1->GetLeft());
			p1->pLeft = p2->pRight;
			p2->pRight = p1;
			pNode->pRight = p2->pLeft;
			p2->pLeft = pNode;
			if (p2->GetBalance() == BalRight) {
				pNode->SetBalance(BalLeft);

			}
			else {
				pNode->SetBalance(BalOK);

			}
			if (p2->GetBalance() == BalLeft) {
				p1->SetBalance(BalRight);

			}
			else {
				p1->SetBalance(BalOK);

			}
			pNode = p2;

		}
		pNode->SetBalance(BalOK);
		HeighIndex = HeightOK;

	}
	return HeighIndex;
	
}              

