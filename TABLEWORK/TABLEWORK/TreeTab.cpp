// ������� �� ���������� �������� � ���� �������� ������
#include "stdafx.h"
#include "TreeTab.h"


int TTreeTable::IsFull() const { // ��������� ?
	PTTreeNode pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}              /*---------------------------------------------*/

PTDatValue TTreeTable::FindRecord(TKey k) { // ����� ������
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot; // ����� ��������� �� �������-����������
	Efficiency = 0;
	while (pNode != NULL) {
		Efficiency++;
		if (pNode->Key == k) break;
		if (pNode->Key <  k) ppRef = &pNode->pRight;
		else ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	SetRetCode(TabOK); return (pNode == NULL) ? NULL : pNode->pValue;
}              /*---------------------------------------------*/

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) { // �������� ������
	if (IsFull()) SetRetCode(TabFull);
	else if (FindRecord(k) != NULL) SetRetCode(TabRecDbl);
	else {
		SetRetCode(TabOK);
		*ppRef = new TTreeNode(k, pVal);
		DataCount++;
	}
}              /*---------------------------------------------*/

void TTreeTable::DelRecord(TKey k) { // ������� ������
	if (FindRecord(k) == NULL) SetRetCode(TabNoRec); // SKIP_ON
	else {
		SetRetCode(TabOK);
		PTTreeNode pNode = *ppRef;
		if (pNode->pRight == NULL) *ppRef = pNode->pLeft; // ���� ������� �����
		else if (pNode->pLeft == NULL) *ppRef = pNode->pRight; // ���� ������� ������
		else { // ��� ������� - ����� �������� ������ � ������ ���������
			PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
			while (pN->pRight != NULL) {
				ppR = &pN->pRight; pN = *ppR;
			} // ������ �������� pNode ������� pN
			pNode->pValue = pN->pValue;   // �������� � pNode
			pNode->Key = pN->Key;
			pNode = pN; *ppR = pN->pLeft; // ����� ���������� pN
		}
		delete pNode;
	}                                                    // SKIP_OFF
}              /*---------------------------------------------*/

// ���������
TKey TTreeTable::GetKey(void) const { // �������� ����� ������� ������
	return (pCurrent == NULL) ? string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePtr(void) const { // ��������� �� ��������
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TTreeTable::Reset(void) { // ���������� �� ������ ������
	PTTreeNode pNode = pCurrent = pRoot;
	while (!St.empty()) St.pop(); // ������� �����
	CurrPos = 0;
	while (pNode != NULL) { // ������� � ������� ����� �������
		St.push(pNode); pCurrent = pNode; pNode = pNode->GetLeft();
	}
	SetRetCode(TabOK);
	return IsTabEnded();
}

int TTreeTable::IsTabEnded(void) const { // ������� ��������� ?
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext(void) { // ������� � ��������� ������
	if (!IsTabEnded() && (pCurrent != NULL)) {  // SKIP_ON
		PTTreeNode pNode = pCurrent = pCurrent->GetRight(); // ������� ������
		St.pop();
		while (pNode != NULL) { // ������� � ������� ����� �������
			St.push(pNode); pCurrent = pNode; pNode = pNode->GetLeft();
		}
		// ���� ������� ������� ���, �� ���������� �� �����
		if ((pCurrent == NULL) && !St.empty()) pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();                           // SKIP_OFF
}

// ������ ������

ostream& operator<<(ostream &os, TTreeTable &tab) {
	//  cout << "������ �������" << endl;
	cout << "Table printing" << endl;
	tab.PrintTreeTab(os, tab.pRoot);
	return os;
}              /*---------------------------------------------*/

void TTreeTable::Draw(void) { // ������ ������ (������� ����� �������)
	//  cout << "������ �������" << endl;
	cout << "Table printing" << endl;
	DrawTreeTab(pRoot, 0);
}              /*---------------------------------------------*/

// ������ ������ � ������ � ������� ����������� � ���������� ������� ������
void TTreeTable::PutValues(PTTreeNode pNode, int Level) {
	if ((pNode != NULL) && (pos<20)){
		PutValues(pNode->pLeft, Level + 1);
		tk[pos] = pNode->Key;
		tl[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level + 1);
	}
}

void TTreeTable::Show(void) { // ������ ������ (������� ������ ����)
	int maxl = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i<pos; i++) if (maxl < tl[i]) maxl = tl[i];
	//  cout << "������ �������" << endl;
	cout << "Table visualization" << endl;
	for (i = 0; i<maxl + 1; i++) { // ����� �����
		pn = 0;
		for (j = 0; j<pos; j++) { // ������ ������ ����� i
			if (tl[j] == i) {
				for (k = 0; k<2 * (j - pn); k++) cout << " ";
				cout << tk[j]; pn = j + 1;
			}
		}
		cout << endl;
	}
}              /*---------------------------------------------*/

// ��������� ������

void TTreeTable::PrintTreeTab(ostream &os, PTTreeNode pNode) {
	if (pNode != NULL) { // ������ ������ � �������� pNode
		PrintTreeTab(os, pNode->pLeft);
		pNode->Print(os); os << endl;
		PrintTreeTab(os, pNode->pRight);
	}
}              /*---------------------------------------------*/

void TTreeTable::DrawTreeTab(PTTreeNode pNode, int Level) {
	if (pNode != NULL) { // ������ ������� � ����������� ������
		DrawTreeTab(pNode->pRight, Level + 1);
		for (int i = 0; i<2 * Level; i++) cout << " ";
		pNode->Print(cout); cout << endl;
		DrawTreeTab(pNode->pLeft, Level + 1);
	}
}              /*---------------------------------------------*/

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) {
	if (pNode != NULL) { // �������� ������ � �������� pNode
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}