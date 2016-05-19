
#include "StdAfx.h"
// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sorttab.cpp - Copyright (c) ������� �.�. 04.09.2000
//
// ������������� �������

#include "Sorttab.h"

// �������� ������������� ������� �� ��������������� �������
TSortTable::TSortTable(const TScanTable &tab) {
	*this = tab;
}

// ��������� ������������� ������� �������� ��������������� �������
TSortTable & TSortTable :: operator =(const TScanTable &tab) {
	if (pRecs != NULL) {
		for (int i = 0; i<DataCount; i++) delete pRecs[i];
		delete[] pRecs; pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i<DataCount; i++)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SortData();
	CurrPos = 0;
	return *this;
}

PTDatValue TSortTable::FindRecord(TKey k) { // ����� ������
	// �������� �����
	int i, i1 = 0, i2 = DataCount - 1; // ������� ������� ������ 

	Efficiency = 0;
	while (i1 <= i2)
	{
		Efficiency++;
		i = (i1 + i2) >> 1;
		if (pRecs[i]->Key == k){ i1 = i + 1; i2 = i; break; }
		if (pRecs[i]->Key > k) i2 = i - 1; else i1 = i + 1;
		if ((i2 < 0) || (pRecs[i2]->Key == k))
			SetRetCode(TabOK); return pRecs[i2]->pValue;
		SetRetCode(TabNoRec); return NULL;
	}
}              /*---------------------------------------------*/

void TSortTable::InsRecord(TKey k, PTDatValue pVal) { // �������� ������
	if (IsFull()) SetRetCode(TabFull);
	else {
		PTDatValue temp = FindRecord(k);
		if (RetCode == TabOK) SetRetCode(TabRecDbl);
		else {
			SetRetCode(TabOK);
			for (int i = DataCount; i>CurrPos; i--) pRecs[i] = pRecs[i - 1]; // �����������
			pRecs[CurrPos] = new TTabRecord(k, pVal);
			DataCount++;
		}
	}
}              /*---------------------------------------------*/

void TSortTable::DelRecord(TKey k) { // ������� ������

	PTDatValue temp = FindRecord(k);
	if (RetCode == TabOK)
	{
		SetRetCode(TabOK);
		for (int i = CurrPos; i<DataCount - 1; i++) pRecs[i] = pRecs[i + 1];
		pRecs[--DataCount] = NULL;
	}

}              /*---------------------------------------------*/

void TSortTable::SortData(void) { // ���������� ������
	Efficiency = 0;
	switch (SortMethod) {
	case INSERT_SORT:
		InsertSort(pRecs, DataCount); // ���������� ����������
		break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount);  // ���������� ��������
		break;
	case QUICK_SORT:
		QuickSort(pRecs, DataCount);  // ������� ����������
		break;
	}
}

// ���������� ���������
void TSortTable::InsertSort(PTTabRecord *pRecs, int DataCount) {
	PTTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1, j; i<DataCount; i++) { // ���� ������� �� ������� i ��� ���������
		pR = pRecs[i]; // ����������� �������
		for (j = i - 1; j>-1; j--)
			if (pRecs[j]->Key > pR->Key) {
				pRecs[j + 1] = pRecs[j]; // ����� ������
				Efficiency++;
			}
			else break;
			pRecs[j + 1] = pR; // �������
	}
}

// ���������� ��������
void TSortTable::MergeSort(PTTabRecord *pRecs, int DataCount) {
	PTTabRecord *pData = pRecs;
	PTTabRecord *pBuff = new PTTabRecord[DataCount];
	PTTabRecord *pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp) // ��������������� ������ ��������� � ������
		for (int i = 0; i<DataCount; i++) pBuff[i] = pData[i];
	delete pTemp;
}

// ���������� �������� - ��������� �����
void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size) {
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2) {
		PTTabRecord *pDat2 = pData + n1, *pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1);  // ���������� "���������" �������
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);   // ������� ������������� "���������" �������
}

// ������� ������������� ��������
void TSortTable::MergeData(PTTabRecord * &pData, PTTabRecord * &pBuff, int n1, int n2) {
	// ��������� ������� ������������� �� ��������� pData ���������������
	// (n1 - ������ ������� �������, n2 - ������ ������� �������)
	// pBuff - ������, � ������� ������������� ������������ ������
	// ����� ������� ��������� pData � pBuff ������������ ����������,
	// �.�. pData ��������� �� ������������ ������, � pBuff - �� ������� ������
	// � ��������� ����� ��������� (����� ��� ������ ����� �������������� ���
	// ������� ����� ��� ����������� ������� ������������� ������



}

// ������� ����������
void TSortTable::QuickSort(PTTabRecord *pRecs, int DataCount) {
	int pivot;  // ������ �������� ��������
	int n1, n2; // ������� ����������� ������ ������
	if (DataCount > 1) {
		QuickSplit(pRecs, DataCount, pivot); // ����������
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);  // ���������� ����������� ������ �������
		QuickSort(pRecs + n1, n2);
	}
}

// ������� ���������� - ����� �������� �������� � ���������� ������
void TSortTable::QuickSplit(PTTabRecord *pData, int Size, int &Pivot) {
	PTTabRecord pPivot = pData[0], pTemp; // pPivot - ��������� �� ������� �������
	int i1 = 1, i2 = Size - 1; // ������� ������ (i1) � ������� (i2) ������
	while (i1 <= i2) { // ����, ���� ����� �� �����������
		// ���� pData[i1]->Key �� ��������� ����� ���. ��-��, ������� ������
		while ((i1<Size) && !(pData[i1]->Key > pPivot->Key)) i1++;
		// ���� pData[i2]->Key ������ ����� ���. ��-��, ������� �����
		while (pData[i2]->Key > pPivot->Key) i2--;
		// ������������ ���������, �� ������� ��������� ��������� ����������
		if (i1 < i2) {
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	// ��������� �������� �������� ����� �������
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2; // i2 - ������ ������� �������� ��������
	Efficiency += Size;
}
