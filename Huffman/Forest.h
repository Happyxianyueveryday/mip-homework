#ifndef FOREST_H 
#define FOREST_H 
#include "TreeNode.h" 
#include <iostream>
#include <string>

struct ListNode
{
	ListNode(TreeNode *_val=NULL):node(_val), next(NULL)
	{
	}

    TreeNode *node;
	ListNode *next;
};

/**
 * Forest: ����ɭ��
 */
class Forest
{
	public:
	// 1. constructor
	Forest();

	// 2. copy controller
	Forest(const Forest &other);                  // �������캯��
	Forest & operator = (const Forest &other);    // ������ֵ�����

	// 3. methods
	void insert(TreeNode *root);           // ��ɭ���в���һ����������֤ɭ������ʱ�临�Ӷ�O(n)
	TreeNode *pop();                             // ��ɭ����ȡ���������С����������֤ɭ������ʱ�临�Ӷ�O(1)
	int length();                                // ���㲢����ɭ�������ĸ�����ʱ�临�Ӷ�O(1)

	// 4. destructor
	~Forest();

	// 5. domains
	private:
	ListNode *head;
	int size;
};

/**
 * Forest: ����һ���յ�ɭ�֣�ɭ���е����Ը�����ֵ��С��������
 */
Forest::Forest()
{
	head=new ListNode(NULL);
	size=0;
}

/**
 * Forest: �������캯��
 */
Forest::Forest(const Forest &other)
{
	head=new ListNode(NULL);
	size=0;

	ListNode *othernow=other.head->next;
	ListNode *now=head->next;

	while(othernow)
	{
		now->next=new ListNode(othernow->node);

		now=now->next;
		othernow=othernow->next;
	}
}

/**
 * operator =: ������ֵ�����
 */
Forest & Forest::operator = (const Forest &other)
{
	if(&other==this)
		return (*this);

	ListNode *temp=head;
	while(temp)
	{
		ListNode *del=temp;
		temp=temp->next;
		delete del;
	}

	head=new ListNode(NULL);
	size=0;

	ListNode *othernow=other.head->next;
	ListNode *now=head->next;

	while(othernow)
	{
		now->next=new ListNode(othernow->node);

		now=now->next;
		othernow=othernow->next; 
	}

	return (*this);
}

/**
 * insert: ��ɭ��������һ����������֤ɭ��������������
 */
void Forest::insert(TreeNode *root)
{
	size+=1;

	// 1. ��Ҫ�������Ϊ�������򽫿������뵽��ǰ����Ϊ������ֵС���κ�һ��ɭ���е���
	if(root==NULL)
	{
		ListNode *newnode=new ListNode(root);
		newnode->next=head->next;
		head->next=newnode;
		return;
	}

	ListNode *now=head->next;
	ListNode *nowprev=head;

	while(now)
	{
		if(now->node!=NULL&&now->node->val>=root->val)    // ���²���������뵽����ĺ���λ�ã�����now��nowprev֮��
			break;
		else
		{
			nowprev=now;
			now=now->next;
		}
	}

	ListNode *newnode=new ListNode(root);
	newnode->next=now;
	nowprev->next=newnode;

	return;
}

/**
 * pop: ��ɭ����ȡ���������С����������֤ɭ������ʱ�临�Ӷ�O(1)
 * return: ɭ���е�ǰ������ֵ��С����
 * warning: ����ʵ�ֵĽӿں�stl�����ͬ��������ɭ���д�����������µ��ø÷���������㶨����NULL
 */
TreeNode *Forest::pop()
{
	if(!head->next)
		return NULL;
	else
	{
		ListNode *temp=head->next;
		TreeNode *res=head->next->node;
		head->next=head->next->next;

		delete temp;
		size-=1;

		return res;
	}
}

/**
 * length: ���㲢����ɭ�������ĸ�����ʱ�临�Ӷ�O(1)
 * return: ɭ�������ĸ���
 */
int Forest::length()
{
	return size;
}

/**
 * ~Forest: �������������
 */
Forest::~Forest()
{
	ListNode *now=head;

	while(now)
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
}

/*
// main����Ԫ����
int main(void)
{
	Forest forest;
	TreeNode *root1=new TreeNode(1);
	TreeNode *root2=new TreeNode(2);
	TreeNode *root3=new TreeNode(5);
	TreeNode *root4=new TreeNode(6);
	TreeNode *root5=new TreeNode(3);
	TreeNode *root6=new TreeNode(4);
	TreeNode *root7=new TreeNode(3);
	forest.insert(root1);
	forest.insert(root2);
	forest.insert(root3);
	forest.insert(root4);
	forest.insert(root5);
	forest.insert(root6);
	forest.insert(root7);
	while(forest.length())
	{
		cout<<forest.pop()->val<<endl;
	}
}
*/

#endif
