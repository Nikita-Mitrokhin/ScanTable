// ����, ���, ���� "������ ����������������-2", �++, ���
//
// scantab.h - Copyright (c) ������� �.�. 03.09.2000
//
// ��������������� �������

#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "arraytab.h"

class TScanTable : public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize) : TArrayTable(Size) {};
    // �������� ������
    virtual PTDatValue FindRecord ( TKey k );                  // ����� ������
    virtual void       InsRecord  ( TKey k, PTDatValue pVal ); // �������� ������
    virtual void       DelRecord  ( TKey k );                  // ������� ������
};
#endif
