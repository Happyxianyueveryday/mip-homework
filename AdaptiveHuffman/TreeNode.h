#ifndef TREE_NODE_H    
#define TREE_NODE_H       
#include <cstddef>     

/**
 * TreeNode: 自适应哈夫曼树结点
 * note: 结点字符值为'#'表示新结点NEW，结点字符值为'*'表示普通的非叶子结点 
 */
struct TreeNode
{
	// 1. constructor
	TreeNode(char _chr, int _weight, bool _flag);    // 基础构造函数 
	
	// 3. domain
	int weight;         // 结点权重 
	char chr;           // 结点字符值 
	TreeNode *left;     // 左子树 
	TreeNode *right;    // 右子树 
	TreeNode *parent;   // 父结点 
	bool flag;          // 标记当前结点是父结点的左子结点还是右子结点，true表示左子结点，false表示右子结点 
};

/**
 * TreeNode: 基础构造函数
 * param _chr: 该哈夫曼树结点的字符
 * param _weight: 该哈夫曼树结点的权重
 * note: 基础构造函数只负责设置结点的字符和权重，结点中的left, right, parent直接设置为空，交由用户负责修改 
 */
TreeNode::TreeNode(char _chr, int _weight, bool _flag):chr(_chr), weight(_weight), left(nullptr), right(nullptr), parent(nullptr), flag(_flag)
{
}

#endif

