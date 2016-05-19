
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tword.cpp - Copyright (c) Гергель В.П. 09.08.2000
//
//   класс объектов-значений для слов
#include "StdAfx.h"
#include "TWord.h"

TDatValue * TWord::GetCopy() { // изготовить копию
	TDatValue *temp = new TWord(Word);
	return temp;
}



// end of tword.cpp
