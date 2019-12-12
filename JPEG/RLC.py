import numpy as np
import math as ma

def rlc(input):
    '''
    : ac: 对输入的8*8图像信号矩阵的AC系数进行游长编码(RLC)，得到一个64维向量
    : param input: np.array, 大小限定为8*8，输入图像信号矩阵
    : return: np.array, 大小为1*64，zig-zag向量化后的图像信号向量
    '''
    res1=[]
    row, col=np.shape(input)[0], np.shape(input)[1]
    for i in range(row):# 遍历上三角部分
        if not i%2:     # 若i为偶数，则从(i, 0)开始到(0, i)
            for k in range(i+1):
                res1.append(input[i-k,0+k])
        else:           # 若i为奇数，则从(0, i)开始到(i, 0)
            for k in range(i+1):
                res1.append(input[0+k,i-k])
    res2=[]
    for i in range(row-1):# 遍历下三角部分
        if not i%2:     # 若i为偶数，则从(row-1-i, col-1)开始到(col-1, row-1-i)
            for k in range(i+1):
                res2.append(input[row-1-i+k, col-1-k])
        else:           # 若i为奇数，则从(row-1, col-1-i)开始到(col-1-i, row-1)
            for k in range(i+1):
                res2.append(input[row-1-k, col-1-i+k])
    res2.reverse()
    res=np.array(res1+res2)
    return res


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    input_image=np.array([
        [32, 6, -1, 0, 0, 0, 0, 0],
        [-1, 0, 0, 0, 0, 0, 0, 0],
        [-1, 0, 1, 0, 0, 0, 0, 0],
        [-1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
    ])
    output_image=rlc(input_image)
    print(output_image)

    input_image=np.array([
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ])
    output_image=rlc(input_image)
    print(output_image)