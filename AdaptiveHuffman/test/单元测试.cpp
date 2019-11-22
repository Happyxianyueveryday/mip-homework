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
 
int main(void) 
{
	// 1. ��ȡ�ļ� 
	string text=readText("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\text.txt");    // ��windowsƽ̨��������Ҫʹ�������ı��༭�����ı��ĵ�ת��ΪGBK���� 
	
	// 2. ����Ӧ���������� 
	string res;
	HuffmanEncoder encoder;
	for(int i=0;i<text.size();i++)
	{
		string code=encoder.encode(text[i]);
		res+=code;
	}
	
	cout<<res.size()<<endl;    // ���ɵĶ������볤��Ϊ412202���أ�Լ50.3kb 
	cout<<res<<endl;  
}
