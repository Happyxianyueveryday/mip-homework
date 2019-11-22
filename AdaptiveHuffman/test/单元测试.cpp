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
    infile.open(file.data());   // ���ļ����������ļ��������� 
    assert(infile.is_open());   // ��ʧ��,�����������Ϣ,����ֹ�������� 

    string s;
    while(getline(infile,s))
    { 
        res=res+s+"\n";
	}
    infile.close();             // �ر��ļ������� 
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
	// 1. ��ȡ�ļ� 
	string text=read_text("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\text.txt");    // ��windowsƽ̨��������Ҫʹ�������ı��༭�����ı��ĵ�ת��ΪGBK���� 
	
	// 2. ����Ӧ���������� 
	string res;
	HuffmanEncoder encoder;
	for(int i=0;i<text.size();i++)
	{
		string code=encoder.encode(text[i]);
		res+=code;
	}
	cout<<res.size()<<endl;    // ���ɵĶ������볤��Ϊ412202���أ�Լ50.3kb 
	//cout<<res<<endl;  
	
	// 3. ���������뱣��Ϊ�ı��ļ�
	ofstream out;
	out.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\out.txt");     // ���к�ɼ��ӱ������½���õ��Ľ����ԭ�ı���ͬ����˱�����ȷ 
	out<<res;
	out.close(); 
	
	// 4. �ı�תΪ���������� 
	int unitsize=sizeof(unsigned int)*8;    // ����unsigned int��λ�� 
	while(res.size()%unitsize)              // ����ַ�����unsigned intλ���������� 
	{
		res.push_back('0');
	}
	
	int size=res.size()/unitsize;
	unsigned int bin[size];  
	for(int i=0;i<size;i++)
	{
		bin[i]=str_to_unsigned(res.substr(i*unitsize, unitsize));
	}
	
	// 5. ���������뱣��Ϊ�������ļ�
	ofstream binout;
	binout.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman2\\out.dat", ios::out|ios::binary);
	binout.write((char *)bin, size*sizeof(unsigned int));
	binout.close(); 
}
