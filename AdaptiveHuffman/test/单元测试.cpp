#include "HuffmanZipper.h"    
#include <iostream>  
#include <string>

using namespace std; 
 
int main(void) 
{
	string input="text.txt";        // �����ļ�·������windowsƽ̨��������Ҫʹ�������ı��༭�����ı��ĵ�ת��ΪGBK���� 
	string output_text="out.txt";   // ����ı��ļ�·��
	string output_binary="out.dat"; // ����ı��ļ�·�� 
	
	HuffmanZipper zipper1(HuffmanZipper::TEXT_IN, HuffmanZipper::TEXT_OUT);      // �����������ļ�ѹ�������ı��ļ����룬�ı��ļ���� 
	HuffmanZipper zipper2(HuffmanZipper::TEXT_IN, HuffmanZipper::BINARY_OUT);    // �����������ļ�ѹ�������ı��ļ����룬�������ļ����
	
	zipper1.zip(input, output_text);
	cout<<"����Ӧ����������ѹ����ɣ��ı��ļ��Ѿ������"<<endl; 
	zipper2.zip(input, output_binary);
	cout<<"����Ӧ����������ѹ����ɣ��������ļ��Ѿ������"<<endl;  
}
