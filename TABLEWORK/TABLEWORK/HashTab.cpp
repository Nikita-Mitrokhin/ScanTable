// Таблицы - базовый класс для таблиц с вычислимым входом
#include "stdafx.h"
#include "hashtab.h"                    string
#include "HashTab.h"					

unsigned long THashTable::HashFunc(const TKey key) {
	unsigned long hashval = 0;
	int Len = key.length();
	for (int i = 0; i<Len; i++)
		hashval = (hashval << 3) + key[i];
	return hashval;
}
