#include "HuffmanCode.h"  
#include <iostream> 
#include <fstream>
#include <ostream> 
#include <cassert>
#include <string>

using namespace std;

string readText(string file)
{
	string res;
    ifstream infile; 
    infile.open(file.data());   // 将文件流对象与文件连接起来 
    assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行 

    string s;
    while(getline(infile,s))
    {
        res=res+s+"\n";
	}
    infile.close();             // 关闭文件输入流 
    return res;
}
 
int main(void) 
{
	// 1. 读取文件 
	string text=readText("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\text.txt");    // 在windows平台上首先需要使用其他文本编辑器将文本文档转化为GBK编码 
	
	map<char, string> dic=HuffmanCode::getHuffmanDict(text);    // 哈夫曼编码表 
	cout<<"哈夫曼编码表如下所示: "<<endl;
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		cout<<a->first<<" "<<a->second<<endl;
	}
	
	// 2. 哈夫曼编码 
	cout<<"原文的哈夫曼编码如下所示: "<<endl;
	string code=HuffmanCode::toHuffmanCode(text, dic); 
	cout<<code<<endl;
	
	ofstream out;
	out.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\out.dat", ios::binary);    // 哈夫曼编码结果使用二进制写入 
	out.write(code.c_str(), code.size());
	out.close();
	
	// 3. 哈夫曼解码 
	cout<<"哈夫曼编码重新解码结果如下所示: "<<endl;
	string retext=HuffmanCode::toText(code, dic);
	cout<<retext<<endl;
	
	ofstream restore;
	restore.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\restore.txt");     // 运行后可见从编码重新解码得到的结果和原文本相同，因此编码正确 
	restore<<retext;
	restore.close();
}
