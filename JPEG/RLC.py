import numpy as np
import math as ma

def rlc(input):
    '''
    : rlc: 对输入的8*8图像信号矩阵的AC系数进行游长编码(RLC)，
    : param input: np.array, 大小限定为8*8，输入图像信号矩阵，其中除了input[0,0]外其他的矩阵系数变量都是AC系数
    : return: list[tuple(int, int)], 输入矩阵的AC系数的游长编码(RLC)结果
    '''
    # 1. zig-zag遍历输入的图像信号矩阵
    tar1=[]
    row, col=np.shape(input)[0], np.shape(input)[1]
    for i in range(row):# 遍历上三角部分
        if not i%2:     # 若i为偶数，则从(i, 0)开始到(0, i)
            for k in range(i+1):
                tar1.append(input[i-k,0+k])
        else:           # 若i为奇数，则从(0, i)开始到(i, 0)
            for k in range(i+1):
                tar1.append(input[0+k,i-k])
    tar2=[]
    for i in range(row-1):# 遍历下三角部分
        if not i%2:     # 若i为偶数，则从(row-1-i, col-1)开始到(col-1, row-1-i)
            for k in range(i+1):
                tar2.append(input[row-1-i+k, col-1-k])
        else:           # 若i为奇数，则从(row-1, col-1-i)开始到(col-1-i, row-1)
            for k in range(i+1):
                tar2.append(input[row-1-k, col-1-i+k])
    tar2.reverse()
    tar=np.array(tar1+tar2)
    # 2. 进行RLC编码为元组的集合
    res=[]
    count=0
    for i in range(1, row*col):
        if tar[i]:
            res.append((count, int(tar[i])))
            count=0
        else:
            count+=1
    res.append((0, 0))
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