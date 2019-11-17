#ifndef HAFFMAN_CODE_H  
#define HAFFMAN_CODE_H
#include "HuffmanTree.h"
#include <iostream>
#include <string>
#include <map>

/**
 * HuffmanCode: 普通哈夫曼编码模块
 */
class HuffmanCode
{
	public:
	static std::map<char, std::string> getHuffmanDict(std::string text);                  // 根据原始文本生成哈夫曼编码词典 
	static std::string toHuffmanCode(std::string text, std::map<char, std::string> dic);  // 根据原始文本和哈夫曼编码词典生成哈夫曼编码 
	static std::string toText(std::string code, std::map<char, std::string> dic);         // 根据哈夫曼编码和哈夫曼编码词典生成原始文本 
};

/** 
 * getHuffmanDict: 根据原始文本生成哈夫曼编码词典
 * param text: 要编码的原始文本
 * return: 原始文本字符的哈夫曼编码词典 
 */
std::map<char, std::string> HuffmanCode::getHuffmanDict(std::string text)                   
{
	// 1. 统计各个字符的出现次数 
	std::map<char, double> freq_dic;    // 字符频率词典
	int len=text.size();
	for(int i=0;i<text.size();i++)
	{
		if(freq_dic.count(text[i]))	
		freq_dic[text[i]]+=1;
		else 
		freq_dic[text[i]]=1;
	} 
	for(auto a=freq_dic.begin();a!=freq_dic.end();a++)
	{
		a->second/=len;
	}
	// 2. 根据各个字符以及各个字符的出现频率生成哈夫曼树
	HuffmanTree tree(freq_dic);
	// 3. 生成哈夫曼编码的字典并返回
	return tree.getHuffmanCode(); 
}

/** 
 * toHuffmanCode: 根据哈夫曼字典将原始字符串编码为哈夫曼编码
 * param text: 原始字符串
 * param dic: 哈夫曼字典 
 * return: 哈夫曼编码 
 */
std::string HuffmanCode::toHuffmanCode(std::string text, std::map<char, std::string> dic)
{
	std::string res;
	for(int i=0;i<text.size();i++)
	{
		res+=dic[text[i]];
	}
	return res;
}

/** 
 * toText: 根据哈夫曼字典将哈夫曼编码还原为原始字符串文本
 * param code: 哈夫曼编码
 * param dic: 哈夫曼字典
 * return: 原始字符串 
 */
std::string HuffmanCode::toText(std::string code, std::map<char, std::string> dic)
{
	// 1. 生成逆映射 
	std::map<std::string, char> redic;    // dic是一对一映射，因此是可逆的 
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		redic[a->second]=a->first;
	}
	// 2. 使用逆映射进行置换 
	std::string temp, res;
	int i=-1;
	while(++i<code.size())
	{
		temp.push_back(code[i]);
		if(redic.count(temp))
		{
			res+=redic[temp];
			temp="";
		}
	}
	return res;
}

#endif 
 
