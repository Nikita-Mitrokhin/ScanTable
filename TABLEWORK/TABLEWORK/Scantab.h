// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// scantab.h - Copyright (c) Гергель В.П. 03.09.2000
//
// Просматриваемые Таблицы

#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "arraytab.h"

class TScanTable : public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize) : TArrayTable(Size) {};
    // основные методы
    virtual PTDatValue FindRecord ( TKey k );                  // найти запись
    virtual void       InsRecord  ( TKey k, PTDatValue pVal ); // вставить запись
    virtual void       DelRecord  ( TKey k );                  // удалить запись
};
#endif
