import numpy as np
import math as ma
import Huffman as hf


def invert_str(input):
    '''
    : invert_str: 取反二进制字符串
    : param input: 二进制字符串输入
    : return: 取反后的二进制字符串
    '''
    return input.replace('1', '2').replace('0', '1').replace('2', '0')


def binarize(input):
    '''
    : binarize: 将输入的数字转化为二进制和位数的元组
    : param input: int, 整数
    : return: (int, str), 输入整数的二进制表示，元组的第一个整数为二进制表示的位数，元组的第二个整数为二进制字符串的长度
    '''
    temp=input
    temp_bin=(bin(abs(temp))[2:]) if temp>=0 else invert_str(bin(abs(temp))[2:])
    temp_len=len(temp_bin)
    return (temp_len, temp_bin)


def ec_ac(input):
    '''
    : ec_ac: AC系数的熵编码模块
    : param input: list[tuple(int, int)], 单个8*8图像的AC系数经过RLC编码得到的输入元组序列，其中元组的第一个整数为游长，第二个整数为游长后遇到的第一个值
    : return: (dict{tuple(int, int), str}, list[tuple(str, str)]), 其中的字典为(游长, 二进制值位数)的哈夫曼编码映射表，list为编码结果
    '''
    for i in range(len(input)):  # 将输入元组列表中元组的第二个值使用二进制编码
        input[i]=(input[i][0], binarize(input[i][1]))               # input[i]=tuple(int, (int, str))=(游长, (二进制值位数, 二进制值表示))
        input[i]=((input[i][0], input[i][1][0]), input[i][1][1])    # input[i]=tuple((int, int), str))=((游长, 二进制值位数), 二进制值表示))
    
    extend_input=[]
    for x in input:
        if x[0][0]>15:   # 游长大于15，则分拆为一系列的(15, 0)，使得每个元组的游长均小于等于15
            for i in range(ma.floor(x[0][0]/15)):
                extend_input.append(((15, 0), ''))
            extend_input.append(((x[0][0]%15, x[0][1]), x[1]))
        else:
            extend_input.append(x)
    
    num_lis=[]   # 输入的(游长, 二进制值位数)去重集合
    num_freq=[]  # 对应输入的出现频率
    for x in extend_input:
        if x[0] in num_lis:
            pass
        else:
            num_lis.append(x[0])
            temp=0
            for y in extend_input:
                if y[0]==x[0]:
                    temp+=1
            num_freq.append(temp)
    
    hftree=hf.build_huffman_tree(num_lis, num_freq)      # 创建哈夫曼树
    dic=hf.generate_huffman_code(hftree)                 # 从哈夫曼树生成哈夫曼编码

    for i in range(len(extend_input)):
        extend_input[i]=(dic[extend_input[i][0]], extend_input[i][1])

    return (dic, extend_input)


def ec_dc(input):
    '''
    : ec_dc: DC系数的熵编码模块
    : param input: list[tuple(int, str)], 各个8*8图像的DC系数经过DPCM编码得到的输入元组序列
    : return: (dict{int, str}, list[tuple(str, str)]), 该元组实际为(哈夫曼编码的编码字典，哈夫曼编码结果)
    : note: 对于DC系数，使用静态哈夫曼编码编码输入元组序列的第一个整数，即位串长度size；而实际DC系数值的二进制位串无需进行编码
    '''
    num_lis=[]   # 输入的数字去重集合
    num_freq=[]  # 对应数字的出现频率
    for x in input:
        if x[0] in num_lis:
            pass
        else:
            num_lis.append(x[0])
            temp=0
            for y in input:
                if y[0]==x[0]:
                    temp+=1
            num_freq.append(temp)
    hftree=hf.build_huffman_tree(num_lis, num_freq)      # 创建哈夫曼树
    dic=hf.generate_huffman_code(hftree)                 # 从哈夫曼树生成哈夫曼编码
    res=[]
    for x in input:
        res.append((dic[x[0]], x[1]))
    return (dic, res)

if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    input=[(8, '10010110'), (3, '101'), (3, '001'), (2, '11'), (4, '0111')]
    output=ec_dc(input)
    print(output)

    input=[(0, 6), (0, -1), (0, -1), (1, -1), (3, -1), (2, 1), (0, 0)]
    output=ec_ac(input)
    print(output)
    

