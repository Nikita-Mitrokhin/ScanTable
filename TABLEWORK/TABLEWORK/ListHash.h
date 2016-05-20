// Таблицы с вычислимым входом - Метод цепочек

#ifndef __LISTHASH_H
#define __LISTHASH_H

#include "datlist.h"
#include "hashtab.h"

#define TabMaxSize  25

class TListHash : public THashTable {
protected:
	PTDatList *pList; // память для массива указателей на списки записей
	int TabSize;      // размер массива указателей
	int CurrList;     // список, в котором выполнялся поиск
public:
	TListHash(int Size = TabMaxSize);
	~TListHash();
	// информационные методы
	virtual int IsFull() const; // таблица заполнена ?
	// основные методы
	virtual PTDatValue FindRecord(TKey k);                  // найти запись
	virtual void       InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void       DelRecord(TKey k);                  // удалить запись
	// навигация
	virtual int Reset(void);        // установить на первую запись
	virtual int IsTabEnded(void) const;  // таблица завершена ?
	virtual int GoNext(void);        // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	// доступ
	virtual TKey GetKey(void) const;            // ключ текущей записи
	virtual PTDatValue GetValuePtr(void) const; // указатель на значение
};
#endif
