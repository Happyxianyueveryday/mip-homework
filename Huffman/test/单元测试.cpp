#include "HuffmanCode.h"  
#include <iostream>

using namespace std;
 
int main(void) 
{
	string text="abcdabcaba";
	map<char, string> dic=HuffmanCode::getHuffmanDict(text);
	
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		cout<<a->first<<" "<<a->second<<endl;
	}
	
	string code=HuffmanCode::toHuffmanCode(text, dic); 
	string retext=HuffmanCode::toText(code, dic);
	cout<<code<<endl;
	cout<<retext<<endl;
}
