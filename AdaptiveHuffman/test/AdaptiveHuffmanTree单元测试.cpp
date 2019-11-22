#include "AdaptiveHuffmanTree.h" 
#include "TreeNode.h" 
#include <iostream>

using namespace std;

int main(void)
{	
	AdaptiveHuffmanTree tree;
	tree.update_tree('A');
	cout<<tree.to_string()<<endl;
	tree.update_tree('A');
	cout<<tree.to_string()<<endl;
	tree.update_tree('D');
	cout<<tree.to_string()<<endl;
	tree.update_tree('C');
	cout<<tree.to_string()<<endl;
	tree.update_tree('C');
	cout<<tree.to_string()<<endl;
	tree.update_tree('D');
	cout<<tree.to_string()<<endl;
	tree.update_tree('D');
	cout<<tree.to_string()<<endl;
	
	cout<<tree.encode('C')<<endl;
}
