// ”пор€доченные “аблицы

#ifndef __SORTTAB_H
#define __SORTTAB_H

#include "scantab.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class TSortTable : public TScanTable {
protected:
	TSortMethod SortMethod; // индекс меьода сортировки
	void SortData(void);    // сортировка данных
	void InsertSort(PTTabRecord *pMem, int DataCount); // метод вставок
	void MergeSort(PTTabRecord *pMem, int DataCount); // метод сли€ни€
	void MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size);
	void MergeData(PTTabRecord * &pData, PTTabRecord * &pBuff, int n1, int n2);
	void QuickSort(PTTabRecord *pMem, int DataCount); // быстра€ сортировка
	void QuickSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {};
	TSortTable(const TScanTable &tab);
	TSortTable & operator =(const TScanTable &tab);    // присваивание    
	TSortMethod GetSortMethod(void)    { return SortMethod; }
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; }
	// основные методы
	virtual PTDatValue FindRecord(TKey k);                  // найти запись
	virtual void       InsRecord(TKey k, PTDatValue pVal); // вставить запись
	virtual void       DelRecord(TKey k);                  // удалить запись
};
#endif
