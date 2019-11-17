#ifndef TREE_NODE_H   
#define TREE_NODE_H 
#include <cstddef>  

/**
 * HuffmanTree: ����������� 
 */
struct TreeNode
{
	TreeNode(double _val=0, char _chr=' '):val(_val),left(NULL),right(NULL),chr(_chr)
	{
	}

	double val;         // �ַ�����Ƶ�� 
	char chr;           // �ַ� 
	TreeNode *left;     // ������ 
	TreeNode *right;    // ������ 
};

#endif
