import numpy as np
import math as ma


def dpcm(input):
    '''
    : dpcm: 对各个8*8图像块的DC系数进行dpcm编码
    : param input: list[int], 各个图像块的DC系数组成的列表
    : return: np.array, 各个图像块的DC系数组成的输入矩阵的dpcm编码
    '''
    res=[input[0]]
    for i in range(1, len(input)):
        res.append(input[i]-input[i-1])
    return res


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    input_list=[150, 155, 149, 152, 144]
    output_list=dpcm(input_list)
    print(output_list)