//   ����� ��������-�������� ��� ����
#include "StdAfx.h"
#include "TWord.h"

TDatValue * TWord::GetCopy() { // ���������� �����
	TDatValue *temp = new TWord(Word);
	return temp;
}



// end of tword.cpp
