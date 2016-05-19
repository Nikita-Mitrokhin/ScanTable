
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// ttable.h - Copyright (c) Гергель В.П. 30.08.2000
//
// Таблицы - базовый класс

#ifndef __TTABLE_H
#define __TTABLE_H

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include "TDataCom.h"
#include "trecord.h"
using namespace std;

#define TabOK        0  // ошибок нет
#define TabEmpty  -101  // таблица полна
#define TabFull   -102  // таблица пуста
#define TabNoRec  -103  // нет записи
#define TabRecDbl -104  // дублирование записи
#define TabNoMem  -105  // нет памяти

class TTable : public TDataCom {
protected:
	int DataCount;  // количество записей в таблице
	int Efficiency; // показатель эффективности выполнения операции
public:
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};
	// информационные методы
	int GetDataCount()   const { return DataCount; } // к-во записей
	int GetEfficiency()  const { return   Efficiency; } // эффективность
	int IsEmpty()        const { return DataCount == 0; } // пуста ?
	virtual int IsFull() const = 0;                       // заполнена ?
	// основные методы
	virtual PTDatValue FindRecord(TKey k) = 0;         // найти запись
	virtual void       InsRecord(TKey k, PTDatValue pVal) = 0; // вставить
	virtual void       DelRecord(TKey k) = 0;         // удалить запись
	// навигация
	virtual int Reset(void) = 0;  // установить на первую запись
	virtual int IsTabEnded(void) const = 0;  // таблица завершена ?
	virtual int GoNext(void) = 0;  // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	// доступ
	virtual TKey GetKey(void) const = 0;
	virtual PTDatValue GetValuePtr(void) const = 0;
	// Печать таблицы
	friend ostream& operator<<(ostream &os, TTable &tab) {
		//  cout << "Печать таблицы" << endl;
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) {
			os << " Key: " << tab.GetKey()
				<< " Val: " << tab.GetValuePtr();  os << endl;
		}
		return os;
	}
};
#endif
