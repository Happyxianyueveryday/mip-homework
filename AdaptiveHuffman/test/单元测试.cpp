#include "HuffmanZipper.h"    
#include <iostream>  
#include <string>

using namespace std; 
 
int main(void) 
{
	string input="text.txt";        // 输入文件路径，在windows平台上首先需要使用其他文本编辑器将文本文档转化为GBK编码 
	string output_text="out.txt";   // 输出文本文件路径
	string output_binary="out.dat"; // 输出文本文件路径 
	
	HuffmanZipper zipper1(HuffmanZipper::TEXT_IN, HuffmanZipper::TEXT_OUT);      // 哈夫曼编码文件压缩器：文本文件输入，文本文件输出 
	HuffmanZipper zipper2(HuffmanZipper::TEXT_IN, HuffmanZipper::BINARY_OUT);    // 哈夫曼编码文件压缩器：文本文件输入，二进制文件输出
	
	zipper1.zip(input, output_text);
	cout<<"自适应哈夫曼编码压缩完成，文本文件已经输出。"<<endl; 
	zipper2.zip(input, output_binary);
	cout<<"自适应哈夫曼编码压缩完成，二进制文件已经输出。"<<endl;  
}
