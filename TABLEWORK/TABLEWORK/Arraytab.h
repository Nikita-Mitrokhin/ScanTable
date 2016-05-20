// ������� - ������� ����� ��� ������ � ����������� �������

#ifndef __ARRAYTAB_H
#define __ARRAYTAB_H

#include "ttable.h"

#define TabMaxSize  25

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
	PTTabRecord *pRecs; // ������ ��� ������� �������
	int TabSize;        // ����. ����. �-�� �������
	int CurrPos;        // ����� �������� ������ (��������� �� 0)
public:
	TArrayTable(int Size = TabMaxSize) {
		pRecs = new PTTabRecord[Size];
		for (int i = 0; i<Size; i++) pRecs[i] = NULL;
		TabSize = Size; DataCount = CurrPos = 0;
	}
	~TArrayTable() {
		for (int i = 0; i<DataCount; i++)
			delete pRecs[i];
		delete[] pRecs;
	}
	// �������������� ������
	virtual int IsFull() const {                     // ������� ��������� ?
		return DataCount >= TabSize;
	}
	int GetTabSize() const { return TabSize; }       // �-�� �������
	// ������
	virtual TKey GetKey(void) const { return GetKey(CURRENT_POS); } // ����
	virtual PTDatValue GetValuePtr(void) const {   // ��������� �� ��������
		return GetValuePtr(CURRENT_POS);
	}
	virtual TKey GetKey(TDataPos mode) const;            // ����
	virtual PTDatValue GetValuePtr(TDataPos mode) const; // ����-�� �� ������.
	// ���������
	virtual int Reset(void);          // ���������� �� ������ ������
	virtual int IsTabEnded(void) const;    // ������� ��������� ?
	virtual int GoNext(void);          // ������� � ��������� ������
	// (=1 ����� ���������� GoNext ��� ��������� ������ �������)
	virtual int SetCurrentPos(int pos);     // ���������� ������� ������
	int GetCurrentPos(void) const {         // �������� ����� ������� ������
		return CurrPos;
	}
	friend TSortTable;
};
#endif
