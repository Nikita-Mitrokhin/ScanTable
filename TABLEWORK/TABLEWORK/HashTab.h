// Таблицы - базовый класс для таблиц с вычислимым входом

#ifndef __HASHTAB_H
#define __HASHTAB_H

#include "ttable.h"

class TTabRecord;

class THashTable : public TTable {
protected:  // хеш-функция
	virtual unsigned long HashFunc(const TKey key);
public:
	THashTable() : TTable() {}
};
#endif
