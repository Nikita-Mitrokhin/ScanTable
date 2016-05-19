
#include "StdAfx.h"
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sorttab.cpp - Copyright (c) Гергель В.П. 04.09.2000
//
// Упорядоченные Таблицы

#include "Sorttab.h"

// создание упорядоченной таблицы по просматриваемой таблице
TSortTable::TSortTable(const TScanTable &tab) {
	*this = tab;
}

// присвание упорядоченной таблицы значения просматриваемой таблицы
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

PTDatValue TSortTable::FindRecord(TKey k) { // найти запись
	// двоичный поиск
	int i, i1 = 0, i2 = DataCount - 1; // границы области поиска 

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

void TSortTable::InsRecord(TKey k, PTDatValue pVal) { // вставить запись
	if (IsFull()) SetRetCode(TabFull);
	else {
		PTDatValue temp = FindRecord(k);
		if (RetCode == TabOK) SetRetCode(TabRecDbl);
		else {
			SetRetCode(TabOK);
			for (int i = DataCount; i>CurrPos; i--) pRecs[i] = pRecs[i - 1]; // перепаковка
			pRecs[CurrPos] = new TTabRecord(k, pVal);
			DataCount++;
		}
	}
}              /*---------------------------------------------*/

void TSortTable::DelRecord(TKey k) { // удалить запись

	PTDatValue temp = FindRecord(k);
	if (RetCode == TabOK)
	{
		SetRetCode(TabOK);
		for (int i = CurrPos; i<DataCount - 1; i++) pRecs[i] = pRecs[i + 1];
		pRecs[--DataCount] = NULL;
	}

}              /*---------------------------------------------*/

void TSortTable::SortData(void) { // сортировка данных
	Efficiency = 0;
	switch (SortMethod) {
	case INSERT_SORT:
		InsertSort(pRecs, DataCount); // сортировка включением
		break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount);  // сортировка слиянием
		break;
	case QUICK_SORT:
		QuickSort(pRecs, DataCount);  // быстрая сортировка
		break;
	}
}

// сортировка вставками
void TSortTable::InsertSort(PTTabRecord *pRecs, int DataCount) {
	PTTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1, j; i<DataCount; i++) { // блок массива до индекса i уже упордочен
		pR = pRecs[i]; // добавляемый элемент
		for (j = i - 1; j>-1; j--)
			if (pRecs[j]->Key > pR->Key) {
				pRecs[j + 1] = pRecs[j]; // сдвиг вправо
				Efficiency++;
			}
			else break;
			pRecs[j + 1] = pR; // вставка
	}
}

// сортировка слиянием
void TSortTable::MergeSort(PTTabRecord *pRecs, int DataCount) {
	PTTabRecord *pData = pRecs;
	PTTabRecord *pBuff = new PTTabRecord[DataCount];
	PTTabRecord *pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp) // отсортированные данные находятся в буфере
		for (int i = 0; i<DataCount; i++) pBuff[i] = pData[i];
	delete pTemp;
}

// сортировка слиянием - служебный метод
void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size) {
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2) {
		PTTabRecord *pDat2 = pData + n1, *pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1);  // сортировка "половинок" массива
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);   // слияние упорядоченных "половинок" массива
}

// слияние упорядоченных массивов
void TSortTable::MergeData(PTTabRecord * &pData, PTTabRecord * &pBuff, int n1, int n2) {
	// сливаемые массивы располагаются по указателю pData последовательно
	// (n1 - размер первого массива, n2 - размер второго массива)
	// pBuff - массив, в котором располагаются объединенные данные
	// после слияния указатели pData и pBuff обмениваются значениями,
	// т.е. pData указывает на объединенные данные, а pBuff - на область памяти
	// с исходными двумя массивами (далее эта память может использоваться как
	// рабочий буфер для последующих слияний упорядоченных данных



}

// быстрая сортировка
void TSortTable::QuickSort(PTTabRecord *pRecs, int DataCount) {
	int pivot;  // индекс ведущего элемента
	int n1, n2; // размеры разделенных блоков данных
	if (DataCount > 1) {
		QuickSplit(pRecs, DataCount, pivot); // разделение
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);  // сортировка разделенных блоков массива
		QuickSort(pRecs + n1, n2);
	}
}

// быстрая сортировка - выбор ведущего элемента и разделение данных
void TSortTable::QuickSplit(PTTabRecord *pData, int Size, int &Pivot) {
	PTTabRecord pPivot = pData[0], pTemp; // pPivot - указатель на ведущий элемент
	int i1 = 1, i2 = Size - 1; // индексы левого (i1) и правого (i2) блоков
	while (i1 <= i2) { // цикл, пока блоки не пересекутся
		// пока pData[i1]->Key не превышает ключа вед. эл-та, переход вправо
		while ((i1<Size) && !(pData[i1]->Key > pPivot->Key)) i1++;
		// пока pData[i2]->Key меньше ключа вед. эл-та, переход влево
		while (pData[i2]->Key > pPivot->Key) i2--;
		// перестановка элементов, на которых произошла остановка разделения
		if (i1 < i2) {
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	// установка ведущего элемента между блоками
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2; // i2 - индекс позиции ведущего элемента
	Efficiency += Size;
}
