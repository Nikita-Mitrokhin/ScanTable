// Просматриваемые Таблицы
#include "stdafx.h"
#include "scantab.h"

PTDatValue TScanTable::FindRecord(TKey k) { // найти запись
	int i;
	SetRetCode(TabOK);
	for (i = 0; i<DataCount; i++)
		if (pRecs[i]->Key == k) break;
	Efficiency = i + 1;
	if (i<DataCount) { CurrPos = i; return pRecs[i]->pValue; }
	SetRetCode(TabNoRec); return NULL;
}              /*---------------------------------------------*/

void TScanTable::InsRecord(TKey k, PTDatValue pVal) { // вставить запись

	Efficiency = 0;
	if (IsFull())
		SetRetCode(TabFull);
	else
	{
		pRecs[DataCount] = new TTabRecord(k, pVal);
		DataCount++;
		SetRetCode(TabOK);
		Efficiency++;
	}
}
              /*---------------------------------------------*/

void TScanTable::DelRecord(TKey k) { // удалить запись

	PTDatValue temp = FindRecord(k);
	if (temp == NULL) //0
		SetRetCode(TabNoRec);
	else
	{
		SetRetCode(TabOK);
		pRecs[CurrPos] = pRecs[DataCount - 1];
		pRecs[--DataCount] = 0;
	}

}              /*---------------------------------------------*/
