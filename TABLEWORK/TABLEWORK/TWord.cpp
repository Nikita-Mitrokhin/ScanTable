
// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tword.cpp - Copyright (c) ������� �.�. 09.08.2000
//
//   ����� ��������-�������� ��� ����
#include "StdAfx.h"
#include "TWord.h"

TDatValue * TWord::GetCopy() { // ���������� �����
	TDatValue *temp = new TWord(Word);
	return temp;
}



// end of tword.cpp
