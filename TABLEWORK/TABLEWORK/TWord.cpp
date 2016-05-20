//   класс объектов-значений для слов
#include "StdAfx.h"
#include "TWord.h"

TDatValue * TWord::GetCopy() { // изготовить копию
	TDatValue *temp = new TWord(Word);
	return temp;
}



// end of tword.cpp
