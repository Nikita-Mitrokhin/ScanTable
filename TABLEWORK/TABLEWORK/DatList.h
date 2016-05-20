// Cписки

#ifndef __DATLIST_H
#define __DATLIST_H

#include "tdatacom.h"
#include "datlink.h"

#define ListOK        0  // ошибок нет
#define ListEmpty  -101  // список пуст
#define ListNoMem  -102  // нет памяти
#define ListNoPos  -103  // ошибочное положение
// текущего указателя
enum TLinkPos { FIRST, CURRENT, LAST };

class TDatList : public TDataCom {
protected:
	PTDatLink pFirst;    // первое звено
	PTDatLink pLast;     // последнее звено
	PTDatLink pCurrLink; // текущее звено
	PTDatLink pPrevLink; // звено перед текущим
	PTDatLink pStop;     // значение указателя, означающего конец списка (=NULL)
	int CurrPos;         // номер текущего знена (нумерация от 0)
	int ListLen;         // количество звеньев в списке
protected:  // методы
	PTDatLink GetLink(PTDatValue pVal = NULL, PTDatLink pLink = NULL);
	void      DelLink(PTDatLink pLink);   // удаление звена
public:
	TDatList();
	~TDatList() { DelList(); }
	// доступ
	PTDatValue GetDatValue(TLinkPos mode = CURRENT) const; // значение
	virtual int IsEmpty()  const { return pFirst == pStop; }    // список пуст ?
	int GetListLength()    const { return ListLen; }          // к-во звеньев
	// навигация
	int SetCurrentPos(int pos);          // установить текущее звено
	int GetCurrentPos(void) const;       // получить номер текущего звена
	virtual int Reset(void);             // установить на начало списка
	virtual int IsListEnded(void) const; // список завершен ?
	int GoNext(void);                    // сдвиг вправо текущего звена
	// (=1 после применения GoNext для последнего звена списка)
	// вставка звеньев
	virtual void InsFirst(PTDatValue pVal = NULL); // вставить перед первым
	virtual void InsLast(PTDatValue pVal = NULL); // вставить последним
	virtual void InsCurrent(PTDatValue pVal = NULL); // вставить перед текущим
	// удаление звеньев
	virtual void DelFirst(void);                 // удалить первое звено
	virtual void DelCurrent(void);                 // удалить текущее звено
	virtual void DelList(void);                 // удалить весь список
};
typedef TDatList *PTDatList;
#endif