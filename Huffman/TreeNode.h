#ifndef TREE_NODE_H   
#define TREE_NODE_H 
#include <cstddef>  

/**
 * HuffmanTree: 哈夫曼树结点 
 */
struct TreeNode
{
	TreeNode(double _val=0, char _chr=' '):val(_val),left(NULL),right(NULL),chr(_chr)
	{
	}

	double val;         // 字符出现频率 
	char chr;           // 字符 
	TreeNode *left;     // 左子树 
	TreeNode *right;    // 右子树 
};

#endif
