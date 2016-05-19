// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// trecord.cpp Copyright (c) Гергель В.П. 03.09.2000
//
//  класс записей таблицы
#include "StdAfx.h"
#include "trecord.h"

TDatValue * TTabRecord::GetCopy() { // изготовить копию
	TDatValue *temp = new TTabRecord(Key, pValue);
	return temp;
}
// end of trecord.cpp
