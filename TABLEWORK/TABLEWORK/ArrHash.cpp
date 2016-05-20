// Таблицы с вычислимым входом - Открытое перемешивание
#include "stdafx.h"
#include "ArrHash.h"


TArrayHash::TArrayHash(int Size, int Step) : THashTable() {
	pRecs = new PTTabRecord[Size]; TabSize = Size; HashStep = Step;
	for (int i = 0; i<TabSize; i++) pRecs[i] = NULL;
	pMark = new TTabRecord(string(""), NULL);
}              /*---------------------------------------------*/

TArrayHash :: ~TArrayHash() { // деструктор
	for (int i = 0; i<TabSize; i++)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) delete pRecs[i];
	delete[] pRecs;
	delete pMark;
}

// основные методы
PTDatValue TArrayHash::FindRecord(TKey k) { // найти запись
	PTDatValue pValue = NULL;
	FreePos = -1; Efficiency = 0;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i<TabSize; i++) {
		Efficiency++;
		if (pRecs[CurrPos] == NULL) break; // свободная строка - конец поиска
		else if (pRecs[CurrPos] == pMark)   // пустая строка - запоминаем первую
		{
			if (FreePos == -1) FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->Key == k)   // нашли ключ
		{
			pValue = pRecs[CurrPos]->pValue; break;
		}
		CurrPos = GetNextPos(CurrPos);    // открытое перемешивание
	}
	if (pValue == NULL) SetRetCode(TabNoRec); else SetRetCode(TabOK);
	return pValue;
}              /*---------------------------------------------*/

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) { // вставить запись

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



// навигация
int TArrayHash::Reset(void) { // установить на первую запись

	CurrPos = 0;
	return CurrPos;

}              /*---------------------------------------------*/

int TArrayHash::IsTabEnded(void) const { // таблица завершена ?
	return CurrPos >= TabSize;
}              /*---------------------------------------------*/

int TArrayHash::GoNext(void) { // переход к следующей записи
	if (!IsTabEnded()) {
		while (++CurrPos < TabSize) // поиск занятой строки
			if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
	}
	return IsTabEnded();
}              /*---------------------------------------------*/

// доступ
TKey TArrayHash::GetKey(void) const { // значение ключа текущей записи
	return ((CurrPos<0) || (CurrPos >= TabSize)) ? string("") : pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash::GetValuePtr(void) const { // указатель на значение
	return ((CurrPos<0) || (CurrPos >= TabSize)) ? NULL : pRecs[CurrPos]->pValue;
}
