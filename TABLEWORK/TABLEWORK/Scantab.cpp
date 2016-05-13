
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// scantab.cpp - Copyright (c) Гергель В.П. 03.09.2000
//
// Просматриваемые Таблицы
#include "StdAfx.h"
#include "scantab.h"

PTDatValue TScanTable :: FindRecord ( TKey k ) { // найти запись
  int i;
  SetRetCode(TabOK);
  for ( i=0; i<DataCount; i++ )
    if ( pRecs[i]->Key == k ) break;
  Efficiency = i+1;  
  if ( i<DataCount ) { CurrPos = i; return pRecs[i]->pValue; }
  SetRetCode(TabNoRec); return NULL;
}              /*---------------------------------------------*/

void TScanTable :: InsRecord ( TKey k, PTDatValue pVal ) { // вставить запись



  
}              /*---------------------------------------------*/

void TScanTable :: DelRecord ( TKey k ) { // удалить запись



}              /*---------------------------------------------*/
