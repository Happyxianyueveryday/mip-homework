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
 * HuffmanTree: ���������ṹ 
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
 * HuffmanTree: ���ݸ�����Ҷ�ӽ�㹹���������
 * param dic: �ַ�������Ƶ�ʵ�ӳ��� 
 */
HuffmanTree::HuffmanTree(std::map<char, double> dic)
{
	// 1. ���Ƚ�����Ҷ�ӽ�㹹��ɵ�����������ʹ����Щ��������ɭ��
	Forest forest;
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		TreeNode *temp=new TreeNode(a->second, a->first);
		forest.insert(temp);
	}

	// 2. ÿ�δ�ɭ���е���������С����left��right������һ���µĸ���㣬����������left��right�ֱ���Ϊ�¸����������������µĸ�����ֵ�͵���left��right�ĸ�����ֵ֮��
	while(forest.length()>1)
	{
		TreeNode *left=forest.pop();
		TreeNode *right=forest.pop();

		TreeNode *newroot=new TreeNode(left->val+right->val);
		newroot->left=left;
		newroot->right=right;

		forest.insert(newroot);
	}

	// 3. ����ɭ����ʣ�µ�һ�������ǹ�������
	treeroot=forest.pop();
}

/**
 * HuffmanTree: ���ݸ�����Ҷ�ӽ�㹹���������
 * param leaves: ������ַ��ĳ���Ƶ��
 * param words: ����ĸ���Ƶ�ʶ�Ӧ���ַ� 
 * param size: ��������Ĵ�С
 */
HuffmanTree::HuffmanTree(double leaves[], char words[], int size)
{
	// 1. ���Ƚ�����Ҷ�ӽ�㹹��ɵ�����������ʹ����Щ��������ɭ��
	Forest forest;
	for(int i=0;i<size;i++)
	{
		TreeNode *temp=new TreeNode(leaves[i], words[i]);
		forest.insert(temp);
	}

	// 2. ÿ�δ�ɭ���е���������С����left��right������һ���µĸ���㣬����������left��right�ֱ���Ϊ�¸����������������µĸ�����ֵ�͵���left��right�ĸ�����ֵ֮��
	while(forest.length()>1)
	{
		TreeNode *left=forest.pop();
		TreeNode *right=forest.pop();

		TreeNode *newroot=new TreeNode(left->val+right->val);
		newroot->left=left;
		newroot->right=right;

		forest.insert(newroot);
	}

	// 3. ����ɭ����ʣ�µ�һ�������ǹ�������
	treeroot=forest.pop();
}

/**
 * HuffmanTree: �������캯��
 */
HuffmanTree::HuffmanTree(const HuffmanTree &other)
{
	treeroot=__copyTree(other.treeroot);
}

/**
 * operator =: ������ֵ�����
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
 * toString: ����α��������������
 * return: �������Ĺ��������Ĳ�α�������
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
 * getHuffmanCode: �ӹ���������ù���������
 * return: ��Ҷ�ӽ���ֵ�������������ӳ��
 * note: �ӹ��������õ�������������㷨�ǳ����ף���ͨ�����ӽ��ı߼�Ϊ0����ͨ�����ӽ��ı߼�Ϊ1������ÿ��Ҷ�ӽ�㣬�Ӹ���㵽Ҷ�ӽ���·���������0����1����������͵õ����յĹ���������
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

		if(!temp.first->left&&!temp.first->right)  // ������Ҷ�ӽ�㣬�򽫶�Ӧ�Ĺ���������д������
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
 * ~HuffmanTree: �������������
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
 * __copyTree: �������Ŀ���
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
 * __deleteTree: ɾ�������ͷ������ڴ�
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
