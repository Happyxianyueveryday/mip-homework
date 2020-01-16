import numpy as np
import heapq

class TreeNode:
    '''
    : TreeNode: 哈夫曼树结点
    '''
    def __init__(self, _val, _freq, _left=None, _right=None):
        '''
        : __init__: 初始化构造函数
        : param _val: int, 该哈夫曼树结点代表的值，若不是叶子结点则可以标记为None
        : param _freq: double, 该哈夫曼树结点代表值的出现频率
        : param _left: TreeNode, 结点的左子树
        : param _right: TreeNode, 结点的右子树
        '''
        self.left=_left
        self.right=_right
        self.val=_val
        self.freq=_freq

    def __lt__(self, other):
        '''
        : __lt__: 小于运算符'<'
        : note: 比较两个哈夫曼树的大小时，只需要比较根结点的值的频率大小即可
        '''
        return self.freq<other.freq
    
        
def build_huffman_tree(input, input_freq):
    '''
    : huffman_tree: 根据输入的数字序列创建哈夫曼树
    : param input: list[int], 输入的数字序列，本项目中需要进行哈夫曼压缩的仅有数字而无字符
    : param input_freq: list[double], 输入的数字序列的对应出现频率
    : return: TreeNode, 创建的哈夫曼树的根结点
    '''
    node_lis=[TreeNode(input[i], input_freq[i]) for i in range(len(input))]    # 所有输入数据转化为哈夫曼树的结点
    heapq.heapify(node_lis)                  # 树结点建堆

    while len(node_lis)>1:
        left=heapq.heappop(node_lis)         
        right=heapq.heappop(node_lis)
        root=TreeNode(None, left.freq+right.freq)    # 出堆两个哈夫曼树，分别作为新的根结点的左子树和右子树
        root.left=left
        root.right=right
        heapq.heappush(node_lis, root)       # 将新构造的哈夫曼树入堆

    return node_lis[0]


def print_huffman_tree(input):
    '''
    : print_huffman_tree: 层次输出哈夫曼树
    : param input: TreeNode, 待输出的哈夫曼树的根结点
    '''
    que=[input]
    res=[]
    while que:
        temp=que[0]
        que.pop(0)
        res.append(temp.val)
        if temp.left:
            que.append(temp.left)
        if temp.right:
            que.append(temp.right)
    print(res)


def generate_huffman_code(root):
    '''
    : generate_huffman_code: 根据输入的哈夫曼树生成对应的哈夫曼编码
    : param root: TreeNode, 输入的哈夫曼树
    : return: dict{int, str}, 数字和对应的哈夫曼编码
    '''
    que=[(root, '')]
    res={}
    while que:
        temp=que[0]
        que.pop(0)

        if not temp[0].left and not temp[0].right:
            res[temp[0].val]=temp[1]

        if temp[0].left:
            que.append((temp[0].left, temp[1]+'0'))
        if temp[0].right:
            que.append((temp[0].right, temp[1]+'1'))
    return res


if __name__ == "__main__":
    '''
    : __main__: 模块单元测试
    '''
    input=[9,16,5,12,13,45]
    tree=build_huffman_tree(input, input)
    print_huffman_tree(tree)
    res=generate_huffman_code(tree)
    print(res)

