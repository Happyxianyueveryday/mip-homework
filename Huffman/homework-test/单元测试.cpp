#include "HuffmanCode.h"  
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
	
	map<char, string> dic=HuffmanCode::getHuffmanDict(text);    // ����������� 
	cout<<"�����������������ʾ: "<<endl;
	for(auto a=dic.begin();a!=dic.end();a++)
	{
		cout<<a->first<<" "<<a->second<<endl;
	}
	
	// 2. ���������� 
	cout<<"ԭ�ĵĹ���������������ʾ: "<<endl;
	string code=HuffmanCode::toHuffmanCode(text, dic); 
	cout<<code<<endl;
	
	ofstream out;
	out.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\out.dat", ios::binary);    // ������������ʹ�ö�����д�� 
	out.write(code.c_str(), code.size());
	out.close();
	
	// 3. ���������� 
	cout<<"�������������½�����������ʾ: "<<endl;
	string retext=HuffmanCode::toText(code, dic);
	cout<<retext<<endl;
	
	ofstream restore;
	restore.open("C:\\Users\\PZH\\Desktop\\lab2\\huffman1\\restore.txt");     // ���к�ɼ��ӱ������½���õ��Ľ����ԭ�ı���ͬ����˱�����ȷ 
	restore<<retext;
	restore.close();
}
