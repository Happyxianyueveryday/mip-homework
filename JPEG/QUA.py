import numpy as np
import math as ma

BRIGHT_QUANT=np.array([          
    [16, 11, 10, 16, 24, 40, 51, 61],
    [12, 12, 14, 19, 26, 58, 60, 65],
    [14, 13, 16, 24, 40, 57, 69, 56],
    [14, 17, 22, 29, 51, 87, 80, 62],
    [18, 22, 37, 56, 68, 109, 103, 77],
    [24, 35, 55, 64, 81, 104, 113, 92],
    [49, 64, 78, 87, 103, 121, 120, 101],
    [72, 92, 95, 98, 112, 100, 103, 99],
])       # 亮度信号量化矩阵


COLOR_QUANT=np.array([
    [17, 18, 24, 47, 99, 99, 99, 99],
    [18, 21, 26, 66, 99, 99, 99, 99],
    [24, 26, 56, 99, 99, 99, 99, 99],
    [47, 66, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
])      # 色度信号量化矩阵


def quantify(input, quant):
    '''
    : quantify: 对单个矩阵进行量化
    : param input: np.array, 大小为8*8，输入图像的信号矩阵
    : param quant: np.array, 大小为8*8，输入分量的量化矩阵，在JPEG编码过程中限定为BRIGHT_QUANT和COLOR_QUANT两个预设参数矩阵，BRIGHT_QUANT用于亮度信号矩阵的量化，COLOR_QUANT用于颜色信号矩阵的量化
    : return: np.array, 量化后的输出变量矩阵
    '''
    if np.shape(input)!=(8, 8) or np.shape(quant)!=(8, 8):
        raise AssertionError
    else:
        return np.round(input/quant)


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试，测试使用样例请参见中文版教材p179
    '''
    input_mat=np.array([
        [515, 65, -12, 4, 1, 2, -8, 5],
        [-16, 3, 2, 0, 0, -11, -2, 3],
        [-12, 6, 11, -1, 3, 0, 1, 2],
        [-8, 3, -4, 2, -2, -3, -5, -2],
        [0, -2, 7, -5, 4, 0, -1, -4],
        [0, -3, -1, 0, 4, 1, -1, 0],
        [3, -2, -3, 3, 3, -1, -1, -3],
        [-2, 5, -2, 4, -2, 2, -3, 0],
    ])
    output_mat=quantify(input_mat, BRIGHT_QUANT)
    np.set_printoptions(suppress=True)
    print(output_mat)