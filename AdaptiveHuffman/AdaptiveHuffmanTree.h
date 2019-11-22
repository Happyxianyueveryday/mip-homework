#ifndef ADAPTIVE_HUFFMAN_TREE 
#define ADAPTIVE_HUFFMAN_TREE  
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

/** 
 * AdaptiveHuffmanTree: ����Ӧ�������� 
 */ 
class AdaptiveHuffmanTree       
{
	public:
	// 1. constructor
	AdaptiveHuffmanTree(); 	   // ���캯�� 
	
	// 2. copy/move_controller
	AdaptiveHuffmanTree(const AdaptiveHuffmanTree &other);      		// �������캯�� 
	AdaptiveHuffmanTree &operator= (const AdaptiveHuffmanTree &other);  // ������ֵ����� 
	AdaptiveHuffmanTree(AdaptiveHuffmanTree &&other); 					// �ƶ����캯�� 
	AdaptiveHuffmanTree &operator= (AdaptiveHuffmanTree &&other);       // �ƶ���ֵ����� 
	
	// 3. methods
	void update_tree(char chr);               // �������ַ�����̬��������Ӧ��������
	bool encode(char chr, std::string &code); // �����ַ��Ĺ��������� 
	std::string to_string();                  // ��α����������Ӧ�������� 
	
	// 4. destructor
	~AdaptiveHuffmanTree();    // �������� 
	
	private:
	// 5. domain
	TreeNode *treeroot; 
	
	// 6. private methods
	TreeNode *_copy_tree(TreeNode *root, TreeNode *parent=nullptr);      // �ڲ�˽�з���: ��������Ӧ�������� 
	TreeNode *_free_tree(TreeNode *root);                                // �ڲ�˽�з���: �ͷ�����Ӧ��������
	TreeNode *_find_pos(char chr);                                       // �ڲ�˽�з���������Ŀ���� 
	TreeNode *_get_prev(TreeNode *root);                                 // �ڲ�˽�з���: ��ȡ��ǰ����ڵ����α����е���һ�����
	TreeNode *_get_tar(TreeNode *root);                                  // �ڲ�˽�з�������ȡ��α����е�һ��ȨֵΪweight-1�Ľ��  
	TreeNode *_new_node(char _chr, int _weight=1);                       // �ڲ�˽�з�����Ϊ���ַ������½��
	void _update_weight(TreeNode *root);                                 // �ڲ�˽�з���: �������㿪ʼ������ϸ��½��Ȩֵ 
	void _swap_node(TreeNode *root1, TreeNode *root2);                   // �ڲ�˽�з����������������������ϵĽ��
};

/**
 * AdaptiveHuffmanTree: �๹�캯�� 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree():treeroot(nullptr)
{
}

/** 
 * AdaptiveHuffmanTree: �������캯�� 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree(const AdaptiveHuffmanTree &other)
{
	treeroot=_copy_tree(other.treeroot);
} 

/**
 * operator=: ������ֵ����� 
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
 * AdaptiveHuffmanTree: �ƶ����캯�� 
 */
AdaptiveHuffmanTree::AdaptiveHuffmanTree(AdaptiveHuffmanTree &&other)
{
	treeroot=other.treeroot;
	other.treeroot=nullptr;
} 

/** 
 * operator=: �ƶ���ֵ����� 
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
 * update_tree: ����һ���ַ�������������Ӧ�������� 
 * note: update_tree�������ַ����������Ӧ���������ĵ��������㷨��Ϊ���ӣ��������ϸ�ִ�����£�
 *       1. �����������: ��ԭ��������Ϊ�գ���ֱ�Ӳ�����ַ��Ľ��
 *       2. ��α���ԭ������������ÿһ���ڴ���������������ҵ�ǰ�ַ���Ŀ����
 *       3. ��δ���ҵ�Ŀ���㣬����NEW��㴦�²嵱ǰ��ǰ�ַ��Ľ�㣬������������ 
 *       4. �����ҵ���Ŀ���㣬��Ŀ�����Ȩ������1��Ȼ���������ĵ������� 
 *       5. ������������ʼ����ǰ���nowΪĿ���㣬ѭ���������²��裬ֱ����ǰ���nowΪ�����ʱѭ�������� 
 *			(1) �Ӹ���㿪ʼ��α�����ÿ���ڴ��ҵ��󣩹���������ֱ��������һ��Ȩ��ֵ����Ŀ�������ڵ�Ȩ��ֵ��1�Ľ�㣬�����ý���Ŀ����
 *          (2) ���½�����now���ĸ�����Ȩ�أ�������ڸ���㣩�����뽻������һ�����������¸����Ȩ�أ���Ϊ�ý���ֵ������ǰĿ�����Ȩ����ȣ� 
 *          (3) ���µ�ǰ���now����now=now->parent 
 */
void AdaptiveHuffmanTree::update_tree(char chr)
{
	// 1. ��ԭ��������Ϊ�գ���ֱ�Ӳ��뵱ǰ�ַ��Ľ�� 
	if(!treeroot)
	{
		treeroot=_new_node(chr);
		return;
	}
	// 2. ��α����������������ҵ�ǰ�ַ���Ŀ����
	TreeNode *now=_find_pos(chr);
	// 3. ��δ���ҵ�Ŀ���㣬�򴴽�һ���½����뵽NEWԭ�ȵ�λ�� 
	if(now->chr=='#')
	{
		TreeNode *newnode=_new_node(chr);   // �����½�� 
		newnode->parent=now->parent;        // �½��ȡ��ԭ�е�NEW���
		newnode->flag=now->flag;
		if(now->flag)                        
		now->parent->left=newnode;
		else
		now->parent->right=newnode; 
		
		_update_weight(newnode);      // ���ϸ��½��Ȩֵ 
		delete now; 
	}
	// 4. �����ҵ���Ŀ���㣬��Ŀ����Ȩֵ����1��Ȼ������������� 
	else
	{
		now->weight+=1;            // Ŀ����Ȩֵ����1  
		while(now->parent)         // ѭ�������������� 
		{
			TreeNode *tar=_get_tar(now);      // ����Ȩֵ�ȵ�ǰ���С1�Ľ�� 
			if(tar&&tar->left!=now&&tar->right!=now) 
			_swap_node(now, tar);          // ������ҵ������Ľ�㣬�򽻻�������� 
			  
			now->parent->weight=(now->parent->left?now->parent->left->weight:0)+(now->parent->right?now->parent->right->weight:0);    // ���¸����ֵ 
			now=now->parent;    	
		}
	}
} 

/** 
 * encode: �Ե����ַ����ɶ�Ӧ�Ĺ��������� 
 * param chr: ����ĵ����ַ�
 * param code: ��������Ĳ����������ַ��Ĺ��������룻������������û�ж�Ӧ���ַ����򷵻�NEW�Ķ�Ӧ����
 * return: �����������д��ڶ�Ӧ���ַ��򷵻�true�����򷵻�false 
 * note: ʹ����������������ɶ�Ӧ�Ĺ��������� 
 */ 
bool AdaptiveHuffmanTree::encode(char chr, std::string &code)
{
	if(!treeroot)    // ��Ϊ�գ���NEW�Ķ�Ӧ����Ϊ"0" 
	{
		code="0";
		return false;
	}
	
	std::stack<std::pair<TreeNode*, std::string>> sta; 
	sta.push(std::make_pair(treeroot, ""));
	std::string new_code;    // NEW�ı��� 
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
 * to_string: ��α����������Ӧ�������� 
 * return: ���������Ĳ�α�������ַ��� 
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
 * ~AdaptiveHuffmanTree: ���������� 
 */
AdaptiveHuffmanTree::~AdaptiveHuffmanTree()
{
	treeroot=_free_tree(treeroot);
}

/**
 * _copy_tree: �������Ӧ��������
 * param root: �������������
 * param parent: ��ʽ���������ڵݹ���ʹ�ã�Ĭ��ֵΪnullptr����ֹ���ε��ò��� 
 * return: ��ǰ������������� 
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
 * _free_tree: �ͷ�����Ӧ��������
 * param root: ���������ĸ���� 
 * return: ��ָ�뱣�����㶨Ϊnullptr������ʱʹ��ptr=_free_tree(ptr)����ʽ��ֹ��������ָ�� 
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
 * _find_pos: ���������ַ���Ӧ�Ĺ���������� 
 * param chr: Ҫ���ҵĽ�������ַ�
 * return: �����ҵ��������ַ��Ķ�Ӧ��㣬�򷵻ض�Ӧ����ָ�룻��δ���ҵ�d��Ӧ��㣬�򷵻�NEW����ָ�룻����������Ϊ�գ��򷵻ؿս�� 
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
 * _get_tar: ��ȡ���������в�α����е�һ��ȨֵΪ�������1�Һ������㲻��ȵĽ�㣬�����������������Ȩֵ��������Ȩ������ǰ��ȵĽ�� 
 * param root: ��������ҽ�� 
 * return: ���������㽻���Ľ�� 
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
 * _new_node: Ϊ�µ��ַ������µĹ����������
 * param _chr: �½����ַ� 
 * param _weight: �½���Ȩ�أ�Ĭ��ֵΪ1
 * return: ��������¹���������� 
 */
TreeNode *AdaptiveHuffmanTree::_new_node(char _chr, int _weight)
{
	// 1. ���ɸ����
	TreeNode *root=new TreeNode('*', _weight, true);
	// 2. �������ӽ��
	root->left=new TreeNode('#', 0, true); 
	root->left->parent=root;
	// 3. �������ӽ��
	root->right=new TreeNode(_chr, _weight, false);
	root->right->parent=root;
	return root; 
}

/**
 * swap_node: ��������������������������Ǹ���� 
 * param root1: �������1������Ϊ�ǿս�㣬�Ҹ����ǿ� 
 * param root2: �������2������Ϊ�ǿս�㣬�Ҹ����ǿ�
 * note 2: �÷����ڽ����󣬲����½��������������Ȩֵ 
 */
void AdaptiveHuffmanTree::_swap_node(TreeNode *root1, TreeNode *root2)
{
	if(!root1||!root2||!root1->parent||!root2->parent)
	return;
	else
	{
		// 1. ������� 
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
 * _update_weight: ������ϵ���Ȩ�� 
 */
void AdaptiveHuffmanTree::_update_weight(TreeNode *root)
{
	if(!root)
	return;
	 
	TreeNode *temp=root->parent;
	while(temp)
	{
		temp->weight=(temp->left?temp->left->weight:0)+(temp->right?temp->right->weight:0);              // ���¸����ֵ 
		temp=temp->parent;
	}
}

#endif 
