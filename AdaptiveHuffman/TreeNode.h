#ifndef TREE_NODE_H    
#define TREE_NODE_H       
#include <cstddef>     

/**
 * TreeNode: ����Ӧ�����������
 * note: ����ַ�ֵΪ'#'��ʾ�½��NEW������ַ�ֵΪ'*'��ʾ��ͨ�ķ�Ҷ�ӽ�� 
 */
struct TreeNode
{
	// 1. constructor
	TreeNode(char _chr, int _weight, bool _flag);    // �������캯�� 
	
	// 3. domain
	int weight;         // ���Ȩ�� 
	char chr;           // ����ַ�ֵ 
	TreeNode *left;     // ������ 
	TreeNode *right;    // ������ 
	TreeNode *parent;   // ����� 
	bool flag;          // ��ǵ�ǰ����Ǹ��������ӽ�㻹�����ӽ�㣬true��ʾ���ӽ�㣬false��ʾ���ӽ�� 
};

/**
 * TreeNode: �������캯��
 * param _chr: �ù������������ַ�
 * param _weight: �ù�����������Ȩ��
 * note: �������캯��ֻ�������ý����ַ���Ȩ�أ�����е�left, right, parentֱ������Ϊ�գ������û������޸� 
 */
TreeNode::TreeNode(char _chr, int _weight, bool _flag):chr(_chr), weight(_weight), left(nullptr), right(nullptr), parent(nullptr), flag(_flag)
{
}

#endif

