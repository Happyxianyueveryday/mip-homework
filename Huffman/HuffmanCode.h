#ifndef HAFFMAN_CODE_H  
#define HAFFMAN_CODE_H
#include "HuffmanTree.h"
#include <iostream>
#include <string>
#include <map>

/**
 * HuffmanCode: ��ͨ����������ģ��
 */
class HuffmanCode
{
	public:
	static std::map<char, std::string> getHuffmanDict(std::string text);                  // ����ԭʼ�ı����ɹ���������ʵ� 
	static std::string toHuffmanCode(std::string text, std::map<char, std::string> dic);  // ����ԭʼ�ı��͹���������ʵ����ɹ��������� 
	static std::string toText(std::string code, std::map<char, std::string> dic);         // ���ݹ���������͹���������ʵ�����ԭʼ�ı� 
};

/** 
 * getHuffmanDict: ����ԭʼ�ı����ɹ���������ʵ�
 * param text: Ҫ�����ԭʼ�ı�
 * return: ԭʼ�ı��ַ��Ĺ���������ʵ� 
 */
std::map<char, std::string> HuffmanCode::getHuffmanDict(std::string text)                   
{
	// 1. ͳ�Ƹ����ַ��ĳ��ִ��� 
	std::map<char, double> freq_dic;    // �ַ�Ƶ�ʴʵ�
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
	// 2. ���ݸ����ַ��Լ������ַ��ĳ���Ƶ�����ɹ�������
	HuffmanTree tree(freq_dic);
	// 3. ���ɹ�����������ֵ䲢����
	return tree.getHuffmanCode(); 
}

/** 
 * toHuffmanCode: ���ݹ������ֵ佫ԭʼ�ַ�������Ϊ����������
 * param text: ԭʼ�ַ���
 * param dic: �������ֵ� 
 * return: ���������� 
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
 * toText: ���ݹ������ֵ佫���������뻹ԭΪԭʼ�ַ����ı�
 * param code: ����������
 * param dic: �������ֵ�
 * return: ԭʼ�ַ��� 
 */
std::string HuffmanCode::toText(std::string code, std::map<char, std::string> dic)
{
	// 1. ������ӳ�� 
	std::map<std::string, char> redic;    // dic��һ��һӳ�䣬����ǿ���� 
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		redic[a->second]=a->first;
	}
	// 2. ʹ����ӳ������û� 
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
 
