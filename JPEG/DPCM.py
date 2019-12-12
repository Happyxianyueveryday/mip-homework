import numpy as np
import math as ma

def invert_str(input):
    '''
    : invert_str: 取反二进制字符串
    : param input: 二进制字符串输入
    : return: 取反后的二进制字符串
    '''
    return input.replace('1', '2').replace('0', '1').replace('2', '0')


def dpcm(input):
    '''
    : dpcm: 对各个8*8图像块的DC系数进行dpcm编码
    : param input: list[int], 各个图像块的DC系数组成的列表
    : return: list[tuple(int, str)], 各个图像块的DC系数组成的输入矩阵的dpcm编码
    '''
    res=[]
    for i in range(0, len(input)):
        temp=input[i]-input[i-1] if i else input[i]
        temp_bin=(bin(abs(temp))[2:]) if temp>0 else invert_str(bin(abs(temp))[2:])
        temp_len=len(temp_bin)
        res.append((temp_len, temp_bin))
    return res


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    input_list=[150, 155, 149, 152, 144]
    output_list=dpcm(input_list)
    print(output_list)