
// ����, ���, ���� "������ ����������������-2", �++, ���
//
// scantab.cpp - Copyright (c) ������� �.�. 03.09.2000
//
// ��������������� �������
#include "StdAfx.h"
#include "scantab.h"

PTDatValue TScanTable :: FindRecord ( TKey k ) { // ����� ������
  int i;
  SetRetCode(TabOK);
  for ( i=0; i<DataCount; i++ )
    if ( pRecs[i]->Key == k ) break;
  Efficiency = i+1;  
  if ( i<DataCount ) { CurrPos = i; return pRecs[i]->pValue; }
  SetRetCode(TabNoRec); return NULL;
}              /*---------------------------------------------*/

void TScanTable :: InsRecord ( TKey k, PTDatValue pVal ) { // �������� ������



  
}              /*---------------------------------------------*/

void TScanTable :: DelRecord ( TKey k ) { // ������� ������



}              /*---------------------------------------------*/
