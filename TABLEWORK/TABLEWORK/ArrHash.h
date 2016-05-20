// Таблицы с вычислимым входом - Открытое перемешивание

#ifndef __ARRHASH_H
#define __ARRHASH_H

#include "hashtab.h"

#define TabMaxSize  25
#define TabHashStep  5

class TArrayHash : public THashTable {
protected:
	PTTabRecord *pRecs; // память для записей таблицы
	int TabSize;        // макс. возм. к-во записей
	int HashStep;       // шаг вторичного перемешивания
	int FreePos;        // первая своб. строка, обнаруженная при поиске
	int CurrPos;        // строка памяти при завершении поиска
	PTTabRecord  pMark; // маркер для индикации строк с удаленными записями
	// функция открытого перемешивания
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	TArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
	~TArrayHash();
	// информационные методы
	virtual int IsFull() const { return DataCount >= TabSize; } // заполнена ?
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
	virtual TKey GetKey(void) const;      // ключ текущей записи
	virtual PTDatValue GetValuePtr(void) const; // указ-ль на значение
};
#endif

