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
 * HuffmanZipper: ����Ӧ�����������ļ�ѹ���� 
 * note: ����Ӧ�����������ļ�ѹ�����ڲ�ͨ��һ��������������ʵ���ļ�ѹ�� 
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
	void zip(std::string input, std::string output);           // ����ѹ�������ѹ���ļ� 
	
	// 4. destructor
	~HuffmanZipper();              // �������� 
	
	// 5. domain
	static const bool TEXT_IN=true;      // ����ģʽ�������ı��ļ����� 
	static const bool BINARY_IN=false;   // ����ģʽ�������������ļ����� 
	static const bool TEXT_OUT=true;     // ���ģʽ�������ı��ļ�����
	static const bool BINARY_OUT=false;  // ���ģʽ�������������ļ����� 
	
	private:
	HuffmanEncoder *encoder;    // һ���Թ����������� 
	bool in_mode;               // �����ļ�ģʽ          
	bool out_mode;              // ����ļ�ģʽ 
	
	// 6. private methods
	std::string _read_text(std::string file);       // �ı��ļ���ȡ 
	std::string _read_binary(std::string file);     // �������ļ���ȡ
	void _save_text(std::string text, std::string file);      // �ı��ļ�����
	void _save_binary(std::string text, std::string file);    // �������ļ����� 
	unsigned int _str_to_unsigned(std::string str);      // �������ַ���תλ���� 
};

/** 
 * HuffmanZipper: �๹�캯�� 
 * param in_mode: �����ļ�ģʽ��HuffmanZipper::BINARY_IN��ʾ�������ļ����룬HuffmanZipper::TEXT_IN��ʾ�ı��ļ����룬Ĭ��Ϊ�ı��ļ����� 
 * param out_mode: ����ļ�ģʽ��HuffmanZipper::BINARY_OUT��ʾ�������ļ������HuffmanZipper::TEXT_OUT��ʾ�ı��ļ������Ĭ��Ϊ�������ļ���� 
 */
HuffmanZipper::HuffmanZipper(bool _in_mode, bool _out_mode):encoder(nullptr), in_mode(_in_mode), out_mode(_out_mode)
{
}

/** 
 * zip: ����ѹ�������ѹ���ļ�
 * param input: �����ļ�·��
 * param output: ����ļ�·�� 
 */
void HuffmanZipper::zip(std::string input, std::string output)           
{
	// 1. �����ļ���ȡ 
	std::string text=(in_mode==HuffmanZipper::TEXT_IN)?_read_text(input):_read_binary(input);
	// 2. ����Ӧ���������� 
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
	// 3. �����ļ����
	if(out_mode==HuffmanZipper::TEXT_OUT)
	_save_text(res, output);
	else
	_save_binary(res, output);
}

/** 
 * HuffmanZipper: ���������� 
 */
HuffmanZipper::~HuffmanZipper()
{
}

/** 
 * read_text: �ı��ļ���ȡ 
 * param file: �ļ���ȡ·�� 
 * return: �ı��ļ���ȡ���� 
 */
std::string HuffmanZipper::_read_text(std::string file)
{
	std::string res;
    std::ifstream infile; 
    infile.open(file.data());   // ���ļ����������ļ��������� 
    assert(infile.is_open());   // ��ʧ��,�����������Ϣ,����ֹ�������� 

    std::string s;
    while(getline(infile,s))
    { 
        res=res+s+"\n";
	}
    infile.close();             // �ر��ļ������� 
    return res;
}

std::string HuffmanZipper::_read_binary(std::string file)
{
	
} 

/** 
 * save_text: �ı��ļ�����
 * param text: ��������ı� 
 * param file: �ļ�����·�� 
 */
void HuffmanZipper::_save_text(std::string text, std::string file)
{
	std::ofstream outfile;
	outfile.open(file);         // ���ļ���������������� 
	assert(outfile.is_open());   // �ж��Ƿ����ӳɹ� 
	outfile<<text;
	outfile.close(); 
}

/** 
 * save_binary: �������ļ�����
 * param text: ��������ı� 
 * param file: �ļ�����·�� 
 */
void HuffmanZipper::_save_binary(std::string text, std::string file)
{
	// 1. ��������ı�ת��Ϊλ���� 
	int unitsize=sizeof(unsigned int)*8;    // ����unsigned int��λ�� 
	while(text.size()%unitsize)             // ����ı��ַ�����unsigned intλ����������
	{
		text.push_back('0');
	}
	
	int size=text.size()/unitsize;           
	unsigned int bin[size];  
	for(int i=0;i<size;i++)
	{
		bin[i]=_str_to_unsigned(text.substr(i*unitsize, unitsize));  
	}
	
	// 2. ���������뱣��Ϊ�������ļ�
	std::ofstream outfile;
	outfile.open(file, std::ios::out|std::ios::binary);
	outfile.write((char *)bin, size*sizeof(unsigned int));
	outfile.close(); 
}

/**
 * _str_to_unsigned: �������ַ���תλ����
 * param str: ����������ַ���������Ҫ��Ϊ��unsigned int�ı�������ͬ 
 * return: ת���õ���λ���� 
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

