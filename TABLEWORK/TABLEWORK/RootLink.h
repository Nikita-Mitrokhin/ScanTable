// ������� ����� ��� �������

#ifndef __ROOTLINK_H
#define __ROOTLINK_H

#include <iostream>
#include "datvalue.h"

class TRootLink;
typedef TRootLink *PTRootLink;

class TRootLink {
protected:
	PTRootLink  pNext;  // ��������� �� ��������� �����
public:
	TRootLink(PTRootLink pN = NULL) { pNext = pN; }
	PTRootLink  GetNextLink() { return  pNext; }
	void        SetNextLink(PTRootLink  pLink) { pNext = pLink; }
	void        InsNextLink(PTRootLink  pLink) {
		PTRootLink p = pNext;  pNext = pLink;
		if (pLink != NULL) pLink->pNext = p;
	}
	virtual void       SetDatValue(PTDatValue pVal) = 0;
	virtual PTDatValue GetDatValue() = 0;

	friend class TDatList;
};
#endif

// end of rootlink.h