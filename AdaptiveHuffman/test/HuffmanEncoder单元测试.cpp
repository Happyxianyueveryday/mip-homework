#include "HuffmanEncoder.h"  
#include "TreeNode.h"  
#include <iostream>

using namespace std;

int main(void)
{	
	HuffmanEncoder encoder;
	cout<<encoder.encode('A')<<endl;
	cout<<encoder.encode('A')<<endl;
	cout<<encoder.encode('D')<<endl;
	cout<<encoder.encode('C')<<endl;
	cout<<encoder.encode('C')<<endl;
	cout<<encoder.encode('D')<<endl;
	cout<<encoder.encode('D')<<endl;
}
