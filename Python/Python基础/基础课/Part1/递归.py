# coding:utf-8

"""
先排序再用递归法找
"""

test_list = [1, 2313, 34, 131, 43, 131, 334, 3]
list1 = sorted(test_list)

print("递归前的列表为:", list1)


def digui(mylist, find, left=0, right=None):
    if right is None:
        right = len(mylist) - 1
    if left == right:
        if find == mylist[right]:
            return left
        else:
            return -1
    else:
        midpoint = int((left + right) / 2)
        if find > mylist[midpoint]:
            return digui(mylist, find, midpoint + 1, right)
        else:
            return digui(mylist, find, left, midpoint)


print("用递归实现二分法查找数字")
print(digui(list1, 23))
