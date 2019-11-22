#ifndef ADAPTIVE_HUFFMAN_TREE 
#define ADAPTIVE_HUFFMAN_TREE  
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

/** 
 * AdaptiveHuffmanTree: 自适应哈夫曼树 
 */ 
class AdaptiveHuffmanTree       
{
	public:
	// 1. constructor
	AdaptiveHuffmanTree(); 	   // 构造函数 
	
	// 2. copy/move_controller
	AdaptiveHuffmanTree(const AdaptiveHuffmanTree &other);      		// 拷贝构造函数 
	AdaptiveHuffmanTree &operator= (const AdaptiveHuffmanTree &other);  // 拷贝赋值运算符 
	AdaptiveHuffmanTree(AdaptiveHuffmanTree &&other); 					// 移动构造函数 
	AdaptiveHuffmanTree &operator= (AdaptiveHuffmanTree &&other);       // 移动赋值运算符 
	
	// 3. methods
	void update_tree(char chr);               // 接受新字符并动态更新自适应哈夫曼树
	bool encode(char chr, std::string &code); // 生成字符的哈夫曼编码 
	std::string to_string();                  // 层次遍历输出自适应哈夫曼树 
	
	// 4. destructor
	~AdaptiveHuffmanTree();    // 析构函数 
	
	private:
	// 5. domain
	TreeNode *treeroot; 
	
	// 6. private methods
	TreeNode *_copy_tree(TreeNode *root, TreeNode *parent=nullptr);      // 内部私有方法: 拷贝自适应哈夫曼树 
	TreeNode *_free_tree(TreeNode *root);                                // 内部私有方法: 释放自适应哈夫曼树
	TreeNode *_find_pos(char chr);                                       // 内部私有方法：查找目标结点 
	TreeNode *_get_prev(TreeNode *root);                                 // 内部私有方法: 获取当前结点在倒序层次遍历中的上一个结点
	TreeNode *_get_tar(TreeNode *root);                                  // 内部私有方法：获取层次遍历中第一个权值为weight-1的结点  
	TreeNode *_new_node(char _chr, int _weight=1);                       // 内部私有方法：为新字符生成新结点
	void _update_weight(TreeNode *root);                                 // 内部私有方法: 从输入结点开始逐层向上更新结点权值 
	void _swap_node(TreeNode *root1, TreeNode *root2);                   // 内部私有方法：交换两个哈夫曼树上的结点
};

/**
 * AdaptiveHuffmanTree: 类构造函数 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree():treeroot(nullptr)
{
}

/** 
 * AdaptiveHuffmanTree: 拷贝构造函数 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree(const AdaptiveHuffmanTree &other)
{
	treeroot=_copy_tree(other.treeroot);
} 

/**
 * operator=: 拷贝赋值运算符 
 */
AdaptiveHuffmanTree &AdaptiveHuffmanTree::operator= (const AdaptiveHuffmanTree &other)
{
	if(&other==this)
	return (*this);
	
	treeroot=_free_tree(treeroot);
	treeroot=_copy_tree(other.treeroot);
	
	return (*this);
} 

/** 
 * AdaptiveHuffmanTree: 移动构造函数 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree(AdaptiveHuffmanTree &&other)
{
	treeroot=other.treeroot;
	other.treeroot=nullptr;
} 

/** 
 * operator=: 移动赋值运算符 
 */
AdaptiveHuffmanTree &AdaptiveHuffmanTree::operator= (AdaptiveHuffmanTree &&other)
{
	if(&other==this)
	return (*this);
	
	treeroot=other.treeroot;
	other.treeroot=nullptr;
	
	return (*this);
}

/**
 * update_tree: 处理一个字符，并更新自适应哈夫曼树 
 * note: update_tree负责处理字符后进行自适应哈夫曼树的调整，该算法较为复杂，其流程严格执行如下：
 *       1. 处理特殊情况: 若原哈夫曼树为空，则直接插入该字符的结点
 *       2. 层次遍历原哈夫曼树，在每一层内从右向左遍历，查找当前字符的目标结点
 *       3. 若未查找到目标结点，则在NEW结点处新插当前当前字符的结点，结束所有流程 
 *       4. 若查找到了目标结点，则将目标结点的权重自增1，然后进行下面的调整操作 
 *       5. 调整操作：初始化当前结点now为目标结点，循环进行以下步骤，直到当前结点now为根结点时循环结束： 
 *			(1) 从根结点开始层次遍历（每层内从右到左）哈夫曼树，直到遇到第一个权重值等于目标结点现在的权重值减1的结点，交换该结点和目标结点
 *          (2) 更新交换后now结点的父结点的权重（如果存在父结点）（参与交换的另一个结点无需更新父结点权重，因为该结点的值和自增前目标结点的权重相等） 
 *          (3) 更新当前结点now，即now=now->parent 
 */
void AdaptiveHuffmanTree::update_tree(char chr)
{
	// 1. 若原哈夫曼树为空，则直接插入当前字符的结点 
	if(!treeroot)
	{
		treeroot=_new_node(chr);
		return;
	}
	// 2. 层次遍历哈夫曼树，查找当前字符的目标结点
	TreeNode *now=_find_pos(chr);
	// 3. 若未查找到目标结点，则创建一个新结点插入到NEW原先的位置 
	if(now->chr=='#')
	{
		TreeNode *newnode=_new_node(chr);   // 生成新结点 
		newnode->parent=now->parent;        // 新结点取代原有的NEW结点
		newnode->flag=now->flag;
		if(now->flag)                        
		now->parent->left=newnode;
		else
		now->parent->right=newnode; 
		
		_update_weight(newnode);      // 向上更新结点权值 
		delete now; 
	}
	// 4. 若查找到了目标结点，则将目标结点权值增加1，然后调整哈夫曼树 
	else
	{
		now->weight+=1;            // 目标结点权值增加1  
		while(now->parent)         // 循环调整哈夫曼树 
		{
			TreeNode *tar=_get_tar(now);      // 查找权值比当前结点小1的结点 
			if(tar&&tar->left!=now&&tar->right!=now) 
			_swap_node(now, tar);          // 如果查找到这样的结点，则交换两个结点 
			  
			now->parent->weight=(now->parent->left?now->parent->left->weight:0)+(now->parent->right?now->parent->right->weight:0);    // 更新父结点值 
			now=now->parent;    	
		}
	}
} 

/** 
 * encode: 对单个字符生成对应的哈夫曼编码 
 * param chr: 输入的单个字符
 * param code: 用于输出的参数，输入字符的哈夫曼编码；若哈夫曼树中没有对应的字符，则返回NEW的对应编码
 * return: 若哈夫曼树中存在对应的字符则返回true，否则返回false 
 * note: 使用先序遍历即可生成对应的哈夫曼编码 
 */ 
bool AdaptiveHuffmanTree::encode(char chr, std::string &code)
{
	if(!treeroot)    // 树为空，则NEW的对应编码为"0" 
	{
		code="0";
		return false;
	}
	
	std::stack<std::pair<TreeNode*, std::string>> sta; 
	sta.push(std::make_pair(treeroot, ""));
	std::string new_code;    // NEW的编码 
	while(sta.size())
	{
		auto now=sta.top();
		sta.pop();
		
		if(!now.first->left&&!now.first->right&&now.first->chr==chr)
		{
			code=now.second;
			return true;
		}
		if(now.first->chr=='#')
		new_code=now.second; 
		
		if(now.first->left)
		sta.push(std::make_pair(now.first->left, now.second+"0"));
		if(now.first->right)
		sta.push(std::make_pair(now.first->right, now.second+"1"));
	}
	
	code=new_code;
	return false;
}

/**
 * to_string: 层次遍历输出自适应哈夫曼树 
 * return: 哈夫曼树的层次遍历输出字符串 
 */
std::string AdaptiveHuffmanTree::to_string()
{
	std::string res;
	std::queue<TreeNode *> que;
	que.push(treeroot);
	while(que.size())
	{
		TreeNode *now=que.front();
		que.pop();
		
		std::string chr;
		chr.push_back(now->chr);
		res=res+"("+chr+", "+std::to_string(now->weight)+") ";
		
		if(now->left)
		que.push(now->left);
		if(now->right)
		que.push(now->right);
	}
	return res;
}

/** 
 * ~AdaptiveHuffmanTree: 类析构函数 
 */
AdaptiveHuffmanTree::~AdaptiveHuffmanTree()
{
	treeroot=_free_tree(treeroot);
}

/**
 * _copy_tree: 深拷贝自适应哈夫曼树
 * param root: 哈夫曼树根结点
 * param parent: 形式化参数，在递归中使用，默认值为nullptr，禁止传参到该参数 
 * return: 当前哈夫曼树的深拷贝 
 */
TreeNode *AdaptiveHuffmanTree::_copy_tree(TreeNode *root, TreeNode *parent)
{
	if(!root)
	return nullptr;
	else
	{
		TreeNode *newroot=new TreeNode(root->chr, root->weight, root->flag);
		newroot->parent=parent;
		newroot->left=_copy_tree(root->left, newroot);
		newroot->right=_copy_tree(root->right, newroot);
		return newroot;
	}
}

/** 
 * _free_tree: 释放自适应哈夫曼树
 * param root: 哈夫曼树的根结点 
 * return: 空指针保护，恒定为nullptr，调用时使用ptr=_free_tree(ptr)的形式防止出现悬空指针 
 */
TreeNode *AdaptiveHuffmanTree::_free_tree(TreeNode *root)
{
	if(!root)
	return nullptr;
	else
	{
		root->left=_free_tree(root->left);
		root->right=_free_tree(root->right);
		delete root;
		return nullptr;
	}
}

/**
 * _find_pos: 查找输入字符对应的哈夫曼树结点 
 * param chr: 要查找的结点代表的字符
 * return: 若查找到了输入字符的对应结点，则返回对应结点的指针；若未查找到d对应结点，则返回NEW结点的指针；若哈夫曼树为空，则返回空结点 
 */
TreeNode *AdaptiveHuffmanTree::_find_pos(char chr)
{
	if(!treeroot)
	return nullptr;
	
	TreeNode *res=nullptr, *temp=nullptr;
	std::queue<TreeNode*> que;
	que.push(treeroot);
	while(que.size())
	{
		TreeNode *now=que.front();
		que.pop();
		
		if(now->chr=='#')
		temp=now;
		if(now->chr==chr)
		res=now;
		
		if(now->left)
		que.push(now->left);
		if(now->right)
		que.push(now->right);
	}
	
	if(res)
	return res;
	else
	return temp;
}

/** 
 * _get_tar: 获取哈夫曼树中层次遍历中第一个权值为输入结点减1且和输入结点不相等的结点，即距离输入结点最大，且权值和输入结点权重自增前相等的结点 
 * param root: 输入待查找结点 
 * return: 待和输入结点交换的结点 
 */ 
TreeNode *AdaptiveHuffmanTree::_get_tar(TreeNode *root)
{
	if(!root)
	return nullptr;
	
	std::queue<TreeNode*> que;
	que.push(treeroot);
	while(que.size())
	{
		TreeNode *now=que.front();
		que.pop();
		
		if(now==root)
		return nullptr;
		if(now->weight==root->weight-1)
		return now;
		
		if(now->right)
		que.push(now->right);
		if(now->left)
		que.push(now->left);
	}
	return nullptr;
} 

/**
 * _new_node: 为新的字符生成新的哈夫曼树结点
 * param _chr: 新结点的字符 
 * param _weight: 新结点的权重，默认值为1
 * return: 输入结点的新哈夫曼树结点 
 */
TreeNode *AdaptiveHuffmanTree::_new_node(char _chr, int _weight)
{
	// 1. 生成根结点
	TreeNode *root=new TreeNode('*', _weight, true);
	// 2. 生成左子结点
	root->left=new TreeNode('#', 0, true); 
	root->left->parent=root;
	// 3. 生成右子结点
	root->right=new TreeNode(_chr, _weight, false);
	root->right->parent=root;
	return root; 
}

/**
 * swap_node: 哈夫曼树特殊操作：交换两个非根结点 
 * param root1: 交换结点1，必须为非空结点，且父结点非空 
 * param root2: 交换结点2，必须为非空结点，且父结点非空
 * note 2: 该方法在交换后，不更新交换后各个父结点的权值 
 */
void AdaptiveHuffmanTree::_swap_node(TreeNode *root1, TreeNode *root2)
{
	if(!root1||!root2||!root1->parent||!root2->parent)
	return;
	else
	{
		// 1. 交换结点 
		if(root1->flag)
		root1->parent->left=root2;
		else
		root1->parent->right=root2;
		
		if(root2->flag)
		root2->parent->left=root1;
		else
		root2->parent->right=root1;
		
		TreeNode *tempnode=root1->parent;
		root1->parent=root2->parent;
		root2->parent=tempnode; 
		
		bool tempflag=root1->flag;
		root1->flag=root2->flag;
		root2->flag=tempflag;
	}
}

/** 
 * _update_weight: 逐层向上调整权重 
 */
void AdaptiveHuffmanTree::_update_weight(TreeNode *root)
{
	if(!root)
	return;
	 
	TreeNode *temp=root->parent;
	while(temp)
	{
		temp->weight=(temp->left?temp->left->weight:0)+(temp->right?temp->right->weight:0);              // 更新父结点值 
		temp=temp->parent;
	}
}

#endif 
