// ������� - ������� (�����������) ����� ��������-�������� ��� ��������
#include "stdafx.h"
#include "TreeNode.h"

TDatValue * TTreeNode::GetCopy() { // ���������� �����
	TTreeNode *temp = new TTreeNode(Key, pValue, NULL, NULL);
	return temp;
}
// end of treenode.cpp
