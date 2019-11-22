#include "HuffmanEncoder.h"  
#include <iostream>  
#include <fstream>
#include <ostream> 
#include <cassert>
#include <string>
#include <cmath>

using namespace std; 

string read_text(string file)
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

unsigned int str_to_unsigned(string str)
{
	unsigned int exp=0, res=0;
	for(int i=str.size()-1;i>=0;i--)
	{
		if(str[i]=='1') 
		res+=pow(2, exp);
		exp+=1;
	}
	return res;
}
 
int main(void) 
{
	// 1. 读取文件 
	string text=read_text("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\text.txt");    // 在windows平台上首先需要使用其他文本编辑器将文本文档转化为GBK编码 
	
	// 2. 自适应哈夫曼编码 
	string res;
	HuffmanEncoder encoder;
	for(int i=0;i<text.size();i++)
	{
		string code=encoder.encode(text[i]);
		res+=code;
	}
	cout<<res.size()<<endl;    // 生成的二进制码长度为412202比特，约50.3kb 
	//cout<<res<<endl;  
	
	// 3. 哈夫曼编码保存为文本文件
	ofstream out;
	out.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\out.txt");     // 运行后可见从编码重新解码得到的结果和原文本相同，因此编码正确 
	out<<res;
	out.close(); 
	
	// 4. 文本转为二进制序列 
	int unitsize=sizeof(unsigned int)*8;    // 单个unsigned int的位数 
	while(res.size()%unitsize)              // 填充字符串到unsigned int位数的整数倍 
	{
		res.push_back('0');
	}
	
	int size=res.size()/unitsize;
	unsigned int bin[size];  
	for(int i=0;i<size;i++)
	{
		bin[i]=str_to_unsigned(res.substr(i*unitsize, unitsize));
	}
	
	// 5. 哈夫曼编码保存为二进制文件
	ofstream binout;
	binout.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\out.dat", ios::out|ios::binary);
	binout.write((char *)bin, size*sizeof(unsigned int));
	binout.close(); 
}
