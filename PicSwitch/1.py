from PIL import Image
import numpy as np
import cv2
import sys
import os

# 1. 读取原始图片
im1 = Image.open(sys.path[0]+"\\1.jpg")
# im1.show()
print(im1.size)   # (1024, 682)

im2 = Image.open(sys.path[0]+"\\2.jpg")
# im2.show()
print(im2.size)   # (1000, 715)

# 2. 拼接图片
tar=Image.new('RGB', (1024+1000, 715))
tar.paste(im1, (0, 0, 1024, 682))
tar.paste(im2, (1024, 0, 2024, 715))
# tar.show()

# 3. 通过滑动固定大小为(1024, 682)的窗口生成一连串切换的图片
tar=np.array(tar)    # (715, 2024, 3)
print(np.shape(tar))

for i in range(0, 2024-1024):
    temp=tar[:, i:i+1024, :]
    # print(np.shape(temp))
    img = Image.fromarray(temp.astype('uint8')).convert('RGB')
    img.save(sys.path[0]+'\mov'+'\\'+str(i)+'.jpg')

# 4. 将图片合成视频
fps = 10
size = (1024, 682)
videowriter = cv2.VideoWriter("result.avi", cv2.VideoWriter_fourcc('D', 'I', 'V', 'X'), fps, size)   
for i in range(0, 2024-1024):
    img = cv2.imread(sys.path[0]+'\mov'+'\\'+str(i)+'.jpg')
    videowriter.write(img)

