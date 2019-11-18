#ifndef HUFFMAN_TREE_H  
#define HUFFMAN_TREE_H  
#include "Forest.h"  
#include <iostream>
#include <string> 
#include <cstdlib>
#include <map>
#include <vector>
#include <queue>

/**
 * HuffmanTree: 哈夫曼树结构 
 */
class HuffmanTree
{
	public:
	// 1. constructor
	HuffmanTree(std::map<char, double> dic);
	HuffmanTree(double leaves[], char words[], int size);

	// 2. copy controller
	HuffmanTree(const HuffmanTree &other);
	HuffmanTree & operator = (const HuffmanTree &other);

	// 3. methods
	std::string toString();
	std::map<char, std::string> getHuffmanCode();

	// 4. destructor
	~HuffmanTree();

	// 5. domains
	private:
	TreeNode *treeroot;

	TreeNode *__copyTree(TreeNode *root);
	void __deleteTree(TreeNode *root);
};

/**
 * HuffmanTree: 根据给定的叶子结点构造哈夫曼树
 * param dic: 字符到出现频率的映射表 
 */
HuffmanTree::HuffmanTree(std::map<char, double> dic)
{
	// 1. 首先将各个叶子结点构造成单独的树，并使用这些树构建成森林
	Forest forest;
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		TreeNode *temp=new TreeNode(a->second, a->first);
		forest.insert(temp);
	}

	// 2. 每次从森林中弹出两个最小的树left和right，创建一个新的根结点，将弹出的树left和right分别作为新根结点的左右子树，新的根结点的值就等于left和right的根结点的值之和
	while(forest.length()>1)
	{
		TreeNode *left=forest.pop();
		TreeNode *right=forest.pop();

		TreeNode *newroot=new TreeNode(left->val+right->val);
		newroot->left=left;
		newroot->right=right;

		forest.insert(newroot);
	}

	// 3. 最终森林中剩下的一个树就是哈夫曼树
	treeroot=forest.pop();
}

/**
 * HuffmanTree: 根据给定的叶子结点构造哈夫曼树
 * param leaves: 输入的字符的出现频率
 * param words: 输入的各个频率对应的字符 
 * param size: 输入数组的大小
 */
HuffmanTree::HuffmanTree(double leaves[], char words[], int size)
{
	// 1. 首先将各个叶子结点构造成单独的树，并使用这些树构建成森林
	Forest forest;
	for(int i=0;i<size;i++)
	{
		TreeNode *temp=new TreeNode(leaves[i], words[i]);
		forest.insert(temp);
	}

	// 2. 每次从森林中弹出两个最小的树left和right，创建一个新的根结点，将弹出的树left和right分别作为新根结点的左右子树，新的根结点的值就等于left和right的根结点的值之和
	while(forest.length()>1)
	{
		TreeNode *left=forest.pop();
		TreeNode *right=forest.pop();

		TreeNode *newroot=new TreeNode(left->val+right->val);
		newroot->left=left;
		newroot->right=right;

		forest.insert(newroot);
	}

	// 3. 最终森林中剩下的一个树就是哈夫曼树
	treeroot=forest.pop();
}

/**
 * HuffmanTree: 拷贝构造函数
 */
HuffmanTree::HuffmanTree(const HuffmanTree &other)
{
	treeroot=__copyTree(other.treeroot);
}

/**
 * operator =: 拷贝赋值运算符
 */
HuffmanTree & HuffmanTree::operator = (const HuffmanTree &other)
{
	if(&other==this)
		return (*this);

	__deleteTree(treeroot);

	treeroot=__copyTree(other.treeroot);

	return (*this);
}

/**
 * toString: 按层次遍历输出哈夫曼树
 * return: 所构建的哈夫曼树的层次遍历序列
 */
std::string HuffmanTree::toString()
{
	std::string res;

	if(!treeroot)
		return res;

	std::queue<TreeNode *> que;
	que.push(treeroot);

	while(que.size())
	{
		TreeNode *temp=que.front();

		char value[100];
		itoa(temp->val, value, 10);
		res=res+std::string(value)+" ";

		que.pop();

		if(temp->left)
			que.push(temp->left);
		if(temp->right)
			que.push(temp->right);
	}

	return res;
}

/**
 * getHuffmanCode: 从哈夫曼树获得哈夫曼编码
 * return: 从叶子结点的值到哈夫曼编码的映射
 * note: 从哈夫曼树得到哈夫曼编码的算法非常容易，将通向左子结点的边记为0，将通向右子结点的边记为1，对于每个叶子结点，从根结点到叶子结点的路径所代表的0或者1组合起来，就得到最终的哈夫曼编码
 */
std::map<char, std::string> HuffmanTree::getHuffmanCode()
{
	std::map<char, std::string> res;

	if(!treeroot)
		return res;

	std::queue<std::pair<TreeNode *, std::string> > que;
	que.push(std::make_pair(treeroot, ""));

	while(que.size())
	{
		std::pair<TreeNode *, std::string> temp=que.front();

		que.pop();

		if(!temp.first->left&&!temp.first->right)  // 若遇到叶子结点，则将对应的哈夫曼编码写入结果中
		{
			res[temp.first->chr]=temp.second;
		}

		if(temp.first->left)
			que.push(make_pair(temp.first->left, temp.second+"0"));
		if(temp.first->right)
			que.push(make_pair(temp.first->right, temp.second+"1"));
	}

	return res;
}

/**
 * ~HuffmanTree: 本类的析构函数
 */
HuffmanTree::~HuffmanTree()
{
	if(!treeroot)
	return;

	std::queue<TreeNode *> que;
	que.push(treeroot);

	while(que.size())
	{
		TreeNode *temp=que.front();

		que.pop();

		if(temp->left)
			que.push(temp->left);
		if(temp->right)
			que.push(temp->right);

		delete temp;
	}
}

/**
 * __copyTree: 制作树的拷贝
 */
TreeNode *HuffmanTree::__copyTree(TreeNode *root)
{
	if(!root)
		return NULL;
	else if(!root->left&&!root->right)
	{
		TreeNode *res=new TreeNode(root->val);
		return res;
	}
	else
	{
		TreeNode *res=new TreeNode(root->val);
		res->left=__copyTree(root->left);
		res->right=__copyTree(root->right);
		return res;

	}
}

/**
 * __deleteTree: 删除树并释放树的内存
 */
void HuffmanTree::__deleteTree(TreeNode *root)
{
	if(!root)
		return;
	else
	{
		TreeNode *left=root->left;
		TreeNode *right=root->right;

		delete root;
		__deleteTree(left);
		__deleteTree(right);
	}
}

#endif
