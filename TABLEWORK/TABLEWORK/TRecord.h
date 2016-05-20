//  класс объектов-значений для записей таблицы

#ifndef __TRECORD_H
#define __TRECORD_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include "datvalue.h"
using namespace std;

typedef string  TKey;

class TTabRecord : public TDatValue  {
protected:
	TKey        Key;   // ключ записи
	PTDatValue pValue; // указатель на значение
public:
	TTabRecord(TKey k = "", PTDatValue pVal = NULL)
	{
		Key = k; pValue = pVal;
	}
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void       SetValuePtr(PTDatValue p) { pValue = p; }
	PTDatValue GetValuePtr(void)         { return pValue; }
	virtual  TDatValue * GetCopy(); // изготовить копию
	TTabRecord & operator=(TTabRecord &tr) {
		Key = tr.Key; pValue = tr.pValue;
		return *this;
	}
	virtual int  operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int  operator< (const TTabRecord &tr) { return Key  > tr.Key; }
	virtual int  operator> (const TTabRecord &tr) { return Key  < tr.Key; }
protected:
	virtual void Print(ostream &os) { os << Key << " " << pValue; }

	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHash;
	friend class TListHash;
};

typedef TTabRecord *PTTabRecord;

#endif
// end of trecord.h
