#ifndef __DATVALUE_H
#define __DATVALUE_H

#include <iostream>
using namespace std;
class TDatValue;
typedef TDatValue *PTDatValue;

class TDatValue
{
public:
	virtual PTDatValue GetCopy() = 0; // создание копии

	~TDatValue() = default;
};
#endif


