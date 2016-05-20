// ������� � ���������� ������ - �������� �������������
#include "stdafx.h"
#include "ArrHash.h"


TArrayHash::TArrayHash(int Size, int Step) : THashTable() {
	pRecs = new PTTabRecord[Size]; TabSize = Size; HashStep = Step;
	for (int i = 0; i<TabSize; i++) pRecs[i] = NULL;
	pMark = new TTabRecord(string(""), NULL);
}              /*---------------------------------------------*/

TArrayHash :: ~TArrayHash() { // ����������
	for (int i = 0; i<TabSize; i++)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) delete pRecs[i];
	delete[] pRecs;
	delete pMark;
}

// �������� ������
PTDatValue TArrayHash::FindRecord(TKey k) { // ����� ������
	PTDatValue pValue = NULL;
	FreePos = -1; Efficiency = 0;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i<TabSize; i++) {
		Efficiency++;
		if (pRecs[CurrPos] == NULL) break; // ��������� ������ - ����� ������
		else if (pRecs[CurrPos] == pMark)   // ������ ������ - ���������� ������
		{
			if (FreePos == -1) FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->Key == k)   // ����� ����
		{
			pValue = pRecs[CurrPos]->pValue; break;
		}
		CurrPos = GetNextPos(CurrPos);    // �������� �������������
	}
	if (pValue == NULL) SetRetCode(TabNoRec); else SetRetCode(TabOK);
	return pValue;
}              /*---------------------------------------------*/

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) { // �������� ������

	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++) {
		Efficiency++;
		if (pRecs[CurrPos] != nullptr && pRecs[CurrPos]->GetKey() == k)
			return;
		else if (pRecs[CurrPos] == nullptr) {
			pRecs[CurrPos] = new TTabRecord(k, pVal);
			DataCount++;
			return;

		}
		CurrPos = GetNextPos(CurrPos);

	}
	SetRetCode(TabFull);



}              /*---------------------------------------------*/

void TArrayHash::DelRecord(TKey k) {
	PTDatValue record = FindRecord(k);
	if (record != NULL) {
		delete pRecs[CurrPos];
		pRecs[CurrPos] = NULL;
		DataCount--;

	}
	else
		SetRetCode(TabNoRec);

}



// ���������
int TArrayHash::Reset(void) { // ���������� �� ������ ������

	CurrPos = 0;
	return CurrPos;

}              /*---------------------------------------------*/

int TArrayHash::IsTabEnded(void) const { // ������� ��������� ?
	return CurrPos >= TabSize;
}              /*---------------------------------------------*/

int TArrayHash::GoNext(void) { // ������� � ��������� ������
	if (!IsTabEnded()) {
		while (++CurrPos < TabSize) // ����� ������� ������
			if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
	}
	return IsTabEnded();
}              /*---------------------------------------------*/

// ������
TKey TArrayHash::GetKey(void) const { // �������� ����� ������� ������
	return ((CurrPos<0) || (CurrPos >= TabSize)) ? string("") : pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash::GetValuePtr(void) const { // ��������� �� ��������
	return ((CurrPos<0) || (CurrPos >= TabSize)) ? NULL : pRecs[CurrPos]->pValue;
}
