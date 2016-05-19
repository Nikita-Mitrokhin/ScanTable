// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// arraytab.h - Copyright (c) Гергель В.П. 03.09.2000
//
// Таблицы - базовый класс для таблиц с непрерывной памятью
#include "StdAfx.h"
#include "arraytab.h"

TKey TArrayTable::GetKey(TDataPos mode) const { // значение
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS: pos = 0;              break;
		case LAST_POS:  pos = DataCount - 1;    break;
		default:        pos = CurrPos;        break;
		}
	}
	return (pos == -1) ? string("") : pRecs[pos]->Key;
}              /*---------------------------------------------*/

PTDatValue TArrayTable::GetValuePtr(TDataPos mode) const { // значение
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS: pos = 0;              break;
		case LAST_POS:  pos = DataCount - 1;    break;
		default:        pos = CurrPos;        break;
		}
	}
	return (pos == -1) ? NULL : pRecs[pos]->pValue;
}              /*---------------------------------------------*/

int TArrayTable::Reset(void) { // установить на первую запись
	CurrPos = 0;
	return IsTabEnded();
}              /*---------------------------------------------*/

int TArrayTable::IsTabEnded(void) const { // таблица завершена ?
	return CurrPos >= DataCount;
}              /*---------------------------------------------*/

int TArrayTable::GoNext(void) { // переход к следующей записи
	if (!IsTabEnded()) CurrPos++;
	return IsTabEnded();
}              /*---------------------------------------------*/

int TArrayTable::SetCurrentPos(int pos) { // установить текущую запись
	CurrPos = ((pos>-1) && (pos<DataCount)) ? pos : 0;
	return IsTabEnded();
}              /*---------------------------------------------*/
