import numpy as np
import math as ma
from scipy.fftpack import dct,idct

def c(input): 
    '''
    : c: DFT变换中的C函数
    : param input: int, 函数输入变量
    : return: double, 函数输出变量
    ；note: C函数在输入为0的时候，返回2^0.5/2；否则返回1
    '''
    if not input:
        return 2**0.5/2
    else:
        return 1


def dct(input):
    '''
    : dct: 对单个输入矩阵进行8*8的二维离散傅里叶变换
    : param input: 8*8, np.array, 输入的矩阵
    : return: np.array, 输入矩阵的二维DFT变换结果矩阵
    : note 1: 若单个输入矩阵不是8*8的，则直接抛出AssertionError
    : note 2: 实际运行时效率太低，一般使用下面的快速离散傅里叶变换(FFT)
    '''
    if np.shape(input)!=(8, 8):    # 输入矩阵不是8*8的，直接抛出异常
        raise AssertionError
    else:       # 输入矩阵为8*8，进行8*8的二维DFT变换
        row, col=np.shape(input)[0], np.shape(input)[1]   
        res=np.zeros((row, col))    # 初始化结果矩阵
        for u in range(row):
            for v in range(col):
                sum=0.0
                for i in range(row):
                    for j in range(col):
                        sum+=ma.cos((2*i+1)*u*ma.pi/16.0)*ma.cos((2*j+1)*v*ma.pi/16.0)*input[i, j]
                res[u, v]=round(c(u)*c(v)/4.0*sum)
        return res

def fct(input):
    '''
    : fct: 对单个输入矩阵进行8*8的快速离散傅里叶变换
    : param input: 8*8, np.array, 输入的矩阵
    : return: np.array, 输入矩阵的二维DFT变换结果矩阵
    : note: 若单个输入矩阵不是8*8的，则直接抛出AssertionError
    '''
    if np.shape(input)!=(8, 8):    # 输入矩阵不是8*8的，直接抛出异常
        raise AssertionError
    else:
        return dct(input)

if __name__ == "__main__":
    '''
    : __main__: 模块单元测试代码，以中文版教材p179的示例为标准测试
    '''
    test_input=np.array([
        [200, 202, 189, 188, 189, 175, 175, 175],
        [200, 203, 198, 188, 189, 182, 178, 175],
        [203, 200, 200, 195, 200, 187, 185, 175],
        [200, 200, 200, 200, 197, 187, 187, 187],
        [200, 205, 200, 200, 195, 188, 187, 175],
        [200, 200, 200, 200, 200, 190, 187, 175],
        [205, 200, 199, 200, 191, 187, 187, 175],
        [210, 200, 200, 200, 188, 185, 187, 186],
    ])
    test_output=dct(test_input)
    np.set_printoptions(suppress=True)
    print(test_output)