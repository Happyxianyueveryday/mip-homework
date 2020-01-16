import DCT as dct
import QUA as qua
import RLC as rlc
import DPCM as dpcm
import EC as ec
import numpy as np
import math as ma
import cv2
import sys

def img_load(input):
    '''
    : img_load: 读取bmp/jpg文件为YUV图像数值矩阵
    : input: bmp文件路径
    : return: (np.array, np.array, np.array)=(y, u, v), YUV形式的图像数值矩阵
    '''
    img=cv2.imread(input)
    img=cv2.cvtColor(img, cv2.COLOR_RGB2YUV)
    y, u, v=cv2.split(img)
    return (y, u, v)


def mat_divide(input):
    '''
    : mat_divide: 对输入的图像的矩阵进行8*8分割
    : param input: np.array, 矩阵大小不限，输入图像矩阵
    : return: np.array[np.array], 输入图像的8*8分割矩阵
    '''
    # 1. 对输入图像进行填充，行数和列数都填充到8的整数倍
    row, col=np.shape(input)[0], np.shape(input)[1]
    newrow, newcol=ma.ceil(row/8)*8, ma.ceil(col/8)*8
    if newrow!=row or newcol!=col:
        input=np.vstack((input, np.zeros((newrow-row, col))))      # 用0填充原矩阵的行数和列数到8的整数倍
        input=np.hstack((input, np.zeros((newrow, newcol-col))))   
    # 2. 分割为8*8的子矩阵
    input=np.hsplit(input, newcol/8)
    for i in range(int(newcol/8)):
        input[i]=np.vsplit(input[i], newrow/8)
    return input


def channel_zip(input, quant):
    '''
    : channel_zip: 对单个通道着行JPEG压缩
    : param input: 输入图像单通道的矩阵
    : return: tuple=(ac, dc)，元组中的两个元素依次为ac编码结果和dc编码结果
    '''
    # 1. 对输入的通道矩阵进行分割，分割为8*8的图像块
    input=mat_divide(input)
    # 2. 依次ac编码每个分割后的8*8矩阵
    row, col=np.shape(input)[0], np.shape(input)[1]
    ac=np.zeros((row, col)).tolist() # ac系数的编码结果
    dc=[]                            # 各个8*8子矩阵的dc列表
    for i in range(row):
        for k in range(col):
            # 2.1 对8*8矩阵块作DCT变换，该步骤耗时较久
            sub_input=dct.dct(input[i][k])
            # 2.2 结果再使用输入的量化矩阵进行量化
            sub_input=qua.quantify(sub_input, quant)
            dc.append(int(sub_input[0, 0]))
            # 3.3 量化结果再进行ac编码
            sub_ac=rlc.rlc(sub_input)
            sub_ac=ec.ec_ac(sub_ac)
            ac[i][k]=sub_ac
    # 3. 进行dc编码
    dc=dpcm.dpcm(dc)
    dc=ec.ec_dc(dc)
    return (ac, dc)


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    test_input3=sys.path[0]+'\\lena.jpg'
    y, u, v=img_load(test_input3)
    print('亮度Y通道矩阵编码结果:')
    y_output=channel_zip(y, qua.BRIGHT_QUANT)

    with open(sys.path[0]+'\\y_ac.txt',"w") as f:
        f.write(str(y_output[0]))
        print('亮度Y的ac编码结果输出到文件y_ac.txt')
    
    with open(sys.path[0]+'\\y_dc.txt',"w") as f:
        f.write(str(y_output[1]))
        print('亮度Y的dc编码结果输出到文件y_dc.txt')

    print('-----------------------------------------')

    print('色度U通道矩阵编码结果:')
    u_output=channel_zip(u, qua.COLOR_QUANT)

    with open(sys.path[0]+'\\u_ac.txt',"w") as f:
        f.write(str(u_output[0]))
        print('色度U的ac编码结果输出到文件u_ac.txt')
    
    with open(sys.path[0]+'\\u_dc.txt',"w") as f:
        f.write(str(u_output[1]))
        print('色度U的dc编码结果输出到文件u_dc.txt')

    print('-----------------------------------------')

    print('色度V通道矩阵编码结果:')
    v_output=channel_zip(u, qua.COLOR_QUANT)

    with open(sys.path[0]+'\\v_ac.txt',"w") as f:
        f.write(str(v_output[0]))
        print('色度V的ac编码结果输出到文件v_ac.txt')
    
    with open(sys.path[0]+'\\v_dc.txt',"w") as f:
        f.write(str(v_output[1]))
        print('色度V的dc编码结果输出到文件v_dc.txt')



