// Таблицы - базовый (абстрактный) класс объектов-значений для деревьев
#include "stdafx.h"
#include "TreeNode.h"

TDatValue * TTreeNode::GetCopy() { // изготовить копию
	TTreeNode *temp = new TTreeNode(Key, pValue, NULL, NULL);
	return temp;
}
// end of treenode.cpp
