#ifndef HUFFMAN_ENCODER_H  
#define HUFFMAN_ENCODER_H        
#include "AdaptiveHuffmanTree.h"  
#include <iostream>

/**
 * HuffmanEncoder: ����Ӧ����������� 
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
	std::string encode(char chr);     // �Ե����ַ���������Ӧ����������
	std::string to_binary(char chr); 
	
	private:
	// 4. domain
	AdaptiveHuffmanTree tree;
	
	// 5. private methods
	
};

/** 
 * HuffmanEncoder: ���캯�� 
 */
HuffmanEncoder::HuffmanEncoder()
{
}

/** 
 * encode: ʹ�ö�̬������������뵥���ַ� 
 * param chr: ������ĵ����ַ�
 * return: �����ַ�������Ӧ���������� 
 */
std::string HuffmanEncoder::encode(char chr)
{
	std::string code;
	if(tree.encode(chr, code))   // ���������д��ڶ�Ӧ���룬�������Ӧ�ı��� 
	{
		tree.update_tree(chr);   // ������
		return code;	
	} 
	else       // ���������в����ڶ�Ӧ���룬�����NEW�����ַ��ĳ�ʼASCII���� 
	{
		tree.update_tree(chr);   // ������
		return code+to_binary(chr);
	}
}

/** 
 * to_binary: �������ַ�ת��Ϊ������ASCII�� 
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
