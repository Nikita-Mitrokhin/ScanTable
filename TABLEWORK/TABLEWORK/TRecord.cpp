//  ����� ������� �������
#include "StdAfx.h"
#include "trecord.h"

TDatValue * TTabRecord::GetCopy() { // ���������� �����
	TDatValue *temp = new TTabRecord(Key, pValue);
	return temp;
}
// end of trecord.cpp
