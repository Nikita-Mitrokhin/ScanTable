// ����, ���, ���� "������ ����������������-2", �++, ���
//
// trecord.cpp Copyright (c) ������� �.�. 03.09.2000
//
//  ����� ������� �������
#include "StdAfx.h"
#include "trecord.h"

TDatValue * TTabRecord::GetCopy() { // ���������� �����
	TDatValue *temp = new TTabRecord(Key, pValue);
	return temp;
}
// end of trecord.cpp
