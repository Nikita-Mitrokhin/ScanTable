//  класс записей таблицы
#include "StdAfx.h"
#include "trecord.h"

TDatValue * TTabRecord::GetCopy() { // изготовить копию
	TDatValue *temp = new TTabRecord(Key, pValue);
	return temp;
}
// end of trecord.cpp
