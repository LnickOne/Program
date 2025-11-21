# coding:utf-8
import os
import os.path

# os.mkdir("test") #创建目录
# print os.getcwd()
# for item in os.listdir(os.getcwd()):
#     print item

# print os.path.exists("Course-38-1-WebGet.py")  # 检查文件或者目录存不存在
# for item in os.path.split(os.getcwd()):
#     print item

# print os.path.join("C:\Users\manki\Desktop", "Part8")
# print os.path.split("C:\Users\manki\Desktop")

# 第一种读目录所有文件名的方法
# def allpath(path):
#     for item in os.listdir(path):
#         sub_path = os.path.join(path, item)
#         print sub_path
#         if os.path.isdir(sub_path):
#             allpath(sub_path )

# allpath(r"C:\Users\manki\Desktop\Part8")


def allpath2(path):
    lst = os.walk(path)  # 遍历一个目录底下的子目录的所有文件名
    # for root, dirs, files in lst:
    #     print files
    # for root, _, _ in lst:
    #     print root
    # for _, dirs, _ in lst:
    #     print dirs
    for _, _, files in lst:
        print files
allpath2(r"C:\Users\manki\Desktop\Part8")
