// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// treetab.h - Copyright (c) Гергель В.П. 04.09.2000
//
// Таблицы со структурой хранения в виде деревьев поиска

#ifndef __TREETAB_H
#define __TREETAB_H

#include <stack>
#include "ttable.h"
#include "treenode.h"

class TTreeTable : public TTable {
protected:
	PTTreeNode  pRoot;    // указатель на корень дерева
	PTTreeNode *ppRef;    // адрес указателя на вершину-результата в FindRecord
	PTTreeNode  pCurrent; // указатель на текущую вершину
	int CurrPos;          // номер текущей вершины
	stack<PTTreeNode> St; // стек для итератора
	void PrintTreeTab(ostream &os, PTTreeNode pNode); // Печать
	void DrawTreeTab(PTTreeNode pNode, int Level);   // Печать с ярусами
	void DeleteTreeTab(PTTreeNode pNode);              // Удаление
public:
	TTreeTable() : TTable() { CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot); }
	// информационные методы
	virtual int IsFull() const;               // заполнена ?
	// основные методы
	virtual PTDatValue FindRecord(TKey k); // найти запись
	virtual void       InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void       DelRecord(TKey k); // удалить запись
	// навигация
	virtual TKey GetKey(void) const;        // ключ текущей записи
	virtual PTDatValue GetValuePtr(void) const; // указатель на значение
	virtual int Reset(void);          // установить на первую запись
	virtual int IsTabEnded(void) const;    // таблица завершена ?
	virtual int GoNext(void);          // переход к следующей записи
	// (=1 после применения GoNext для последней записи таблицы)
	// Печать таблицы
	friend ostream& operator<<(ostream &os, TTreeTable &tab);
	void Draw(void); // печать дерева (рисунок слева направо)
	void Show(void); // печать дерева (рисунок сверху вниз)
protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTTreeNode pNode, int Level); // служебный метод lkz Show
};
#endif