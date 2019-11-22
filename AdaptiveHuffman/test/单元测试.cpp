#include "HuffmanEncoder.h"  
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
	
	// 2. 自适应哈夫曼编码 
	string res;
	HuffmanEncoder encoder;
	for(int i=0;i<text.size();i++)
	{
		string code=encoder.encode(text[i]);
		res+=code;
	}
	
	cout<<res.size()<<endl;    // 生成的二进制码长度为412202比特，约50.3kb 
	cout<<res<<endl;  
}
