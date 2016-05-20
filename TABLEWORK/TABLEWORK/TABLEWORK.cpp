// Тестирование таблицы

#define _CRT_SECURE_NO_WARNINGS

#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "tword.h"
#include "Scantab.h"
using namespace std;

TScanTable *pTab = NULL;
string *pKeys = NULL;
TWord  *pWords = NULL;
int     DataCount = 0, MemSize;

// заполнение таблицы
void TableGenerator(void) {
	int  MaxKeyValue, RetCode;
	char Line[100];

	cout << "Input the record's number - ";
	cin >> DataCount;
	cout << "Input the Maximum Key Value - ";
	cin >> MaxKeyValue;
	MemSize = DataCount + 10;
	pTab = new TScanTable(MemSize);
	pKeys = new string[MemSize];
	pWords = new TWord[MemSize];
	for (int i = 0; i<DataCount; i++) {
		sprintf(Line, "%d", rand()%MaxKeyValue );
		pKeys[i] = string(Line);
		pWords[i] = TWord("*" + pKeys[i] + "*");
		pTab->InsRecord(pKeys[i], &pWords[i]);
		if ((RetCode = pTab->GetRetCode()) != TabOK) {
			cout << "Retcode: " << RetCode << endl;
		}
	}
}

// выполнение операций обработки таблицы
void TableProcessor(void) {
	int com; string key;
	while (1) {
		cout << "Input Command (0-Exit, 1-Find, 2-Ins, 3-Del, 4-Print) - ";
		cin >> com;
		if (com == 0) break;
		if (com != 4) {
			cout << "Input the key of record - ";
			cin >> key;
		}
		if (com == 1) { // поиск
			cout << " Find " << pTab->FindRecord(key);
			cout << " Effect  = " << pTab->GetEfficiency();
			cout << " RetCode = " << pTab->GetRetCode() << endl;
		}
		if (com == 2) { // вставка
			if (DataCount >= MemSize)
				cout << "MemBuffer is full" << endl;
			else {
				pKeys[DataCount] = key;
				pWords[DataCount] = TWord("*" + key + "*");
				pTab->InsRecord(key, &pWords[DataCount]);
				DataCount++;
				cout << "Insert: RetCode = " << pTab->GetRetCode() << endl;
			}
		}
		if (com == 3) { // удаление
			pTab->DelRecord(key);
			cout << "Delete: RetCode = " << pTab->GetRetCode() << endl;
		}
		if (com == 4) cout << *pTab; // Table printing
	}
}

// оценка сложности операции вставки
void TableEvaluator(void) {
	int  IterCount, k;
	long Total = 0;
	cout << "Input the iteration's number - ";
	cin >> IterCount;
	for (int i = 0; i<IterCount; i++) {
		k = int(rand()%DataCount);
		pTab->FindRecord(pKeys[k]);
		Total += pTab->GetEfficiency();
	}
	cout << "Insert in the table - efficiency evaluation" << endl;
	cout << "Table Size: " << pTab->GetDataCount() << endl;
	cout << "Iterations: " << IterCount << endl;
	cout << "Average Efficiency: " << Total / double(IterCount) << endl;
}


void main() {

	//  cout << "Тестирование программ поддержки таблиц" << endl;
	cout << "Test for the table support system (scan type) " << endl;
	TableGenerator();
	TableProcessor();
	TableEvaluator();
	_getch();
	delete pTab;
	delete[] pKeys;
	delete[] pWords;
}
