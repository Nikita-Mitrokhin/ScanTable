// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tword.h Copyright (c) Гергель В.П. 01.12.2002
//
// Таблицы - класс объектов-значений - слова

#ifndef __TWORD_H
#define __TWORD_H

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include "datvalue.h"
using namespace std;

class TWord : public TDatValue {
  protected:
   string Word;
  public:
    TWord ( string w = "" ) { Word = w; }
    virtual TDatValue * GetCopy(); // изготовить копию
    string  GetWord   ( void )         { return Word; }
    void    SetWord   ( string &w )    { Word = w;    }
    TWord & operator= (const TWord &w) { Word = w.Word; return *this; }
    int     operator==(const TWord &w) { return Word==w.Word; }
  protected:
    virtual void Print(ostream &os) { os << Word; }
};

typedef TWord *PTWord;

#endif
// end of tword.h
