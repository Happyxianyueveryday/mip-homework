#ifndef HUFFMAN_ENCODER_H  
#define HUFFMAN_ENCODER_H        
#include "AdaptiveHuffmanTree.h"  
#include <iostream>

/**
 * HuffmanEncoder: 自适应哈夫曼编码端 
 */
class HuffmanEncoder
{
	public:
	// 1. constructor
	HuffmanEncoder();                        
	
	// 2. copy/move controller
	HuffmanEncoder(const HuffmanEncoder &other) = delete;
	HuffmanEncoder &operator= (const HuffmanEncoder &other) = delete; 
	HuffmanEncoder(HuffmanEncoder &&other) = delete;
	HuffmanEncoder &operator= (HuffmanEncoder &&other) = delete;
	
	// 3. methods
	std::string encode(char chr);     // 对单个字符进行自适应哈夫曼编码
	std::string to_binary(char chr); 
	
	private:
	// 4. domain
	AdaptiveHuffmanTree tree;
	
	// 5. private methods
	
};

/** 
 * HuffmanEncoder: 构造函数 
 */
HuffmanEncoder::HuffmanEncoder()
{
}

/** 
 * encode: 使用动态哈夫曼编码编码单个字符 
 * param chr: 待编码的单个字符
 * return: 输入字符的自适应哈夫曼编码 
 */
std::string HuffmanEncoder::encode(char chr)
{
	std::string code;
	if(tree.encode(chr, code))   // 哈夫曼树中存在对应编码，则输出对应的编码 
	{
		tree.update_tree(chr);   // 更新树
		return code;	
	} 
	else       // 哈夫曼树中不存在对应编码，则输出NEW加上字符的初始ASCII编码 
	{
		tree.update_tree(chr);   // 更新树
		return code+to_binary(chr);
	}
}

/** 
 * to_binary: 将单个字符转化为二进制ASCII码 
 */
std::string HuffmanEncoder::to_binary(char chr)
{
	std::string res;
	int input=static_cast<int>(chr);
	while(input>1)
	{
		res=std::to_string(input%2)+res;
		input/=2;
	}
	res=std::to_string(input)+res;
	return res;
}

#endif
