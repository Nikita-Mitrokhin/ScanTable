// ������� � ���������� ������ - ����� �������
#include "stdafx.h"
#include "ListHash.h"


TListHash::TListHash(int Size) : THashTable() {
	pList = new PTDatList[Size]; TabSize = Size; CurrList = 0;
	for (int i = 0; i<TabSize; i++) pList[i] = new TDatList;
}              /*---------------------------------------------*/

TListHash :: ~TListHash() {
	for (int i = 0; i<TabSize; i++) delete pList[i];
	delete[] pList;
}              /*---------------------------------------------*/

int TListHash::IsFull() const { // ������� ��������� ?
	PTDatLink pLink = new TDatLink();
	int temp = (pLink == NULL);
	delete pLink;
	return temp;
}              /*---------------------------------------------*/

PTDatValue TListHash::FindRecord(TKey k) { // ����� ������
	PTDatValue pValue = NULL;
	CurrList = HashFunc(k) % TabSize;   // ������� �����������
	PTDatList pL = pList[CurrList]; Efficiency = 0;
	for (pL->Reset(); !pL->IsListEnded(); pL->GoNext()) // ����� �� ������
		if (PTTabRecord(pL->GetDatValue())->Key == k)
		{
			pValue = PTTabRecord(pL->GetDatValue())->pValue; break;
		}
	Efficiency = pL->GetCurrentPos() + 1; // ����� ���. ���. = �-�� �������� ������
	if (pValue == NULL) SetRetCode(TabNoRec); else SetRetCode(TabOK);
	return pValue;
}              /*---------------------------------------------*/

void TListHash::InsRecord(TKey k, PTDatValue pVal) { // �������� ������
	CurrList = HashFunc(k) % TabSize;
	PTTabRecord pRec = new TTabRecord(k, pVal);
	pList[CurrList]->InsLast(static_cast<PTDatValue>(pRec));
	DataCount++;
	

}              /*---------------------------------------------*/

void TListHash::DelRecord(TKey k) { // ������� ������
	PTDatValue temp = FindRecord(k);          // ����� � �������
	if (temp != NULL) {
		pList[CurrList]->DelCurrent();
		DataCount--;

	}
	else
		SetRetCode(TabNoRec);

}              /*---------------------------------------------*/

// ���������
int TListHash::Reset(void) { // ���������� �� ������ ������
	CurrList = 0;
	pList[CurrList]->Reset();
	return IsTabEnded();
}              /*---------------------------------------------*/

int TListHash::IsTabEnded(void) const { // ������� ��������� ?
	return CurrList >= TabSize;
}              /*---------------------------------------------*/

int TListHash::GoNext(void) { // ������� � ��������� ������

	if (IsTabEnded())
		SetRetCode(TabFull);
	else {
		pList[CurrList]->GoNext();
		if (pList[CurrList]->IsListEnded())
			while (!IsTabEnded() && pList[CurrList]->IsListEnded())
				CurrList++;

	}
	return GetRetCode();

}              /*---------------------------------------------*/

// ������
TKey TListHash::GetKey(void) const { // �������� ����� ������� ������
	if ((CurrList<0) || (CurrList >= TabSize)) return string("");
	PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
	return (pRec == NULL) ? string("") : pRec->Key;
}              /*---------------------------------------------*/

PTDatValue TListHash::GetValuePtr(void) const { // ��������� �� ��������
	if ((CurrList<0) || (CurrList >= TabSize)) return NULL;
	PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
	return (pRec == NULL) ? NULL : pRec->pValue;
}              /*---------------------------------------------*/
