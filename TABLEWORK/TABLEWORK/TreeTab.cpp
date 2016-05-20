// Таблицы со структурой хранения в виде деревьев поиска
#include "stdafx.h"
#include "TreeTab.h"


int TTreeTable::IsFull() const { // заполнена ?
	PTTreeNode pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}              /*---------------------------------------------*/

PTDatValue TTreeTable::FindRecord(TKey k) { // найти запись
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot; // адрес указателя на вершину-результата
	Efficiency = 0;
	while (pNode != NULL) {
		Efficiency++;
		if (pNode->Key == k) break;
		if (pNode->Key <  k) ppRef = &pNode->pRight;
		else ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	SetRetCode(TabOK); return (pNode == NULL) ? NULL : pNode->pValue;
}              /*---------------------------------------------*/

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) { // вставить запись
	if (IsFull()) SetRetCode(TabFull);
	else if (FindRecord(k) != NULL) SetRetCode(TabRecDbl);
	else {
		SetRetCode(TabOK);
		*ppRef = new TTreeNode(k, pVal);
		DataCount++;
	}
}              /*---------------------------------------------*/

void TTreeTable::DelRecord(TKey k) { // удалить запись
	if (FindRecord(k) == NULL) SetRetCode(TabNoRec); // SKIP_ON
	else {
		SetRetCode(TabOK);
		PTTreeNode pNode = *ppRef;
		if (pNode->pRight == NULL) *ppRef = pNode->pLeft; // один потомок слева
		else if (pNode->pLeft == NULL) *ppRef = pNode->pRight; // один потомок справа
		else { // два потомка - поиск крайнего справа у левого поддерева
			PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
			while (pN->pRight != NULL) {
				ppR = &pN->pRight; pN = *ppR;
			} // вместо удаления pNode удается pN
			pNode->pValue = pN->pValue;   // значение в pNode
			pNode->Key = pN->Key;
			pNode = pN; *ppR = pN->pLeft; // обход удаляемого pN
		}
		delete pNode;
	}                                                    // SKIP_OFF
}              /*---------------------------------------------*/

// навигация
TKey TTreeTable::GetKey(void) const { // значение ключа текущей записи
	return (pCurrent == NULL) ? string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePtr(void) const { // указатель на значение
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TTreeTable::Reset(void) { // установить на первую запись
	PTTreeNode pNode = pCurrent = pRoot;
	while (!St.empty()) St.pop(); // очистка стека
	CurrPos = 0;
	while (pNode != NULL) { // переход к крайней левой вершине
		St.push(pNode); pCurrent = pNode; pNode = pNode->GetLeft();
	}
	SetRetCode(TabOK);
	return IsTabEnded();
}

int TTreeTable::IsTabEnded(void) const { // таблица завершена ?
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext(void) { // переход к следующей записи
	if (!IsTabEnded() && (pCurrent != NULL)) {  // SKIP_ON
		PTTreeNode pNode = pCurrent = pCurrent->GetRight(); // переход вправо
		St.pop();
		while (pNode != NULL) { // переход к крайней левой вершине
			St.push(pNode); pCurrent = pNode; pNode = pNode->GetLeft();
		}
		// если правого потомка нет, то извлечение из стека
		if ((pCurrent == NULL) && !St.empty()) pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();                           // SKIP_OFF
}

// методы печати

ostream& operator<<(ostream &os, TTreeTable &tab) {
	//  cout << "Печать таблицы" << endl;
	cout << "Table printing" << endl;
	tab.PrintTreeTab(os, tab.pRoot);
	return os;
}              /*---------------------------------------------*/

void TTreeTable::Draw(void) { // печать дерева (рисунок слева направо)
	//  cout << "Печать таблицы" << endl;
	cout << "Table printing" << endl;
	DrawTreeTab(pRoot, 0);
}              /*---------------------------------------------*/

// запись ключей в массив в порядке возрастания с запоминаем номеров ярусов
void TTreeTable::PutValues(PTTreeNode pNode, int Level) {
	if ((pNode != NULL) && (pos<20)){
		PutValues(pNode->pLeft, Level + 1);
		tk[pos] = pNode->Key;
		tl[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level + 1);
	}
}

void TTreeTable::Show(void) { // печать дерева (рисунок сверху вниз)
	int maxl = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i<pos; i++) if (maxl < tl[i]) maxl = tl[i];
	//  cout << "Печать таблицы" << endl;
	cout << "Table visualization" << endl;
	for (i = 0; i<maxl + 1; i++) { // номер яруса
		pn = 0;
		for (j = 0; j<pos; j++) { // печать ключей яруса i
			if (tl[j] == i) {
				for (k = 0; k<2 * (j - pn); k++) cout << " ";
				cout << tk[j]; pn = j + 1;
			}
		}
		cout << endl;
	}
}              /*---------------------------------------------*/

// служебные методы

void TTreeTable::PrintTreeTab(ostream &os, PTTreeNode pNode) {
	if (pNode != NULL) { // печать дерева с вершиной pNode
		PrintTreeTab(os, pNode->pLeft);
		pNode->Print(os); os << endl;
		PrintTreeTab(os, pNode->pRight);
	}
}              /*---------------------------------------------*/

void TTreeTable::DrawTreeTab(PTTreeNode pNode, int Level) {
	if (pNode != NULL) { // печать таблицы с соблюдением ярусов
		DrawTreeTab(pNode->pRight, Level + 1);
		for (int i = 0; i<2 * Level; i++) cout << " ";
		pNode->Print(cout); cout << endl;
		DrawTreeTab(pNode->pLeft, Level + 1);
	}
}              /*---------------------------------------------*/

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) {
	if (pNode != NULL) { // удаление дерева с вершиной pNode
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}