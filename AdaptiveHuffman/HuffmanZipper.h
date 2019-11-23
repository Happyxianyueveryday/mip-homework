#ifndef HUFFMAN_ZIPPER_H 
#define HUFFMAN_ZIPPER_H
#include "HuffmanEncoder.h"  
#include <iostream>
#include <string> 
#include <fstream> 
#include <ostream> 
#include <cassert>
#include <cmath>

/**
 * HuffmanZipper: 自适应哈夫曼编码文件压缩器 
 * note: 自适应哈夫曼编码文件压缩器内部通过一个哈夫曼编码器实现文件压缩 
 */
class HuffmanZipper
{
	public: 
	// 1. constructor
	HuffmanZipper(bool _in_mode=HuffmanZipper::TEXT_IN, bool _out_mode=HuffmanZipper::BINARY_OUT);
	
	// 2. copy/move controller
	HuffmanZipper(const HuffmanZipper &other) = delete;
	HuffmanZipper &operator= (const HuffmanZipper &other) = delete;
	HuffmanZipper(HuffmanZipper &&other) = delete;
	HuffmanZipper &operator= (HuffmanZipper &&other) = delete;
	
	// 3. methods
	void zip(std::string input, std::string output);           // 进行压缩并输出压缩文件 
	
	// 4. destructor
	~HuffmanZipper();              // 析构函数 
	
	// 5. domain
	static const bool TEXT_IN=true;      // 输入模式参数：文本文件输入 
	static const bool BINARY_IN=false;   // 输入模式参数：二进制文件输入 
	static const bool TEXT_OUT=true;     // 输出模式参数：文本文件输入
	static const bool BINARY_OUT=false;  // 输出模式参数：二进制文件输入 
	
	private:
	HuffmanEncoder *encoder;    // 一次性哈夫曼编码器 
	bool in_mode;               // 输入文件模式          
	bool out_mode;              // 输出文件模式 
	
	// 6. private methods
	std::string _read_text(std::string file);       // 文本文件读取 
	std::string _read_binary(std::string file);     // 二进制文件读取
	void _save_text(std::string text, std::string file);      // 文本文件保存
	void _save_binary(std::string text, std::string file);    // 二进制文件保存 
	unsigned int _str_to_unsigned(std::string str);      // 二进制字符串转位数组 
};

/** 
 * HuffmanZipper: 类构造函数 
 * param in_mode: 输入文件模式，HuffmanZipper::BINARY_IN表示二进制文件输入，HuffmanZipper::TEXT_IN表示文本文件输入，默认为文本文件输入 
 * param out_mode: 输出文件模式，HuffmanZipper::BINARY_OUT表示二进制文件输出，HuffmanZipper::TEXT_OUT表示文本文件输出，默认为二进制文件输出 
 */
HuffmanZipper::HuffmanZipper(bool _in_mode, bool _out_mode):encoder(nullptr), in_mode(_in_mode), out_mode(_out_mode)
{
}

/** 
 * zip: 进行压缩并输出压缩文件
 * param input: 输入文件路径
 * param output: 输出文件路径 
 */
void HuffmanZipper::zip(std::string input, std::string output)           
{
	// 1. 输入文件读取 
	std::string text=(in_mode==HuffmanZipper::TEXT_IN)?_read_text(input):_read_binary(input);
	// 2. 自适应哈夫曼编码 
	std::string res;
	encoder=new HuffmanEncoder();
	for(int i=0;i<text.size();i++)
	{
		std::string code=encoder->encode(text[i]);
		res+=code;
	}
	delete encoder;
	encoder=nullptr;
	std::cout<<res.size()<<std::endl; 
	// 3. 编码文件输出
	if(out_mode==HuffmanZipper::TEXT_OUT)
	_save_text(res, output);
	else
	_save_binary(res, output);
}

/** 
 * HuffmanZipper: 类析构函数 
 */
HuffmanZipper::~HuffmanZipper()
{
}

/** 
 * read_text: 文本文件读取 
 * param file: 文件读取路径 
 * return: 文本文件读取内容 
 */
std::string HuffmanZipper::_read_text(std::string file)
{
	std::string res;
    std::ifstream infile; 
    infile.open(file.data());   // 将文件流对象与文件连接起来 
    assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行 

    std::string s;
    while(getline(infile,s))
    { 
        res=res+s+"\n";
	}
    infile.close();             // 关闭文件输入流 
    return res;
}

std::string HuffmanZipper::_read_binary(std::string file)
{
	
} 

/** 
 * save_text: 文本文件保存
 * param text: 待保存的文本 
 * param file: 文件保存路径 
 */
void HuffmanZipper::_save_text(std::string text, std::string file)
{
	std::ofstream outfile;
	outfile.open(file);         // 将文件与输出流连接起来 
	assert(outfile.is_open());   // 判断是否连接成功 
	outfile<<text;
	outfile.close(); 
}

/** 
 * save_binary: 二进制文件保存
 * param text: 待保存的文本 
 * param file: 文件保存路径 
 */
void HuffmanZipper::_save_binary(std::string text, std::string file)
{
	// 1. 将输入的文本转换为位数组 
	int unitsize=sizeof(unsigned int)*8;    // 单个unsigned int的位数 
	while(text.size()%unitsize)             // 填充文本字符串到unsigned int位数的整数倍
	{
		text.push_back('0');
	}
	
	int size=text.size()/unitsize;           
	unsigned int bin[size];  
	for(int i=0;i<size;i++)
	{
		bin[i]=_str_to_unsigned(text.substr(i*unitsize, unitsize));  
	}
	
	// 2. 哈夫曼编码保存为二进制文件
	std::ofstream outfile;
	outfile.open(file, std::ios::out|std::ios::binary);
	outfile.write((char *)bin, size*sizeof(unsigned int));
	outfile.close(); 
}

/**
 * _str_to_unsigned: 二进制字符串转位数组
 * param str: 输入二进制字符串，长度要求为和unsigned int的比特数相同 
 * return: 转换得到的位数组 
 */
unsigned int HuffmanZipper::_str_to_unsigned(std::string str)
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

#endif

