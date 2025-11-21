# coding:utf-8


"""
只从电子邮件地址中提取出登录名和域名(包括主域名和顶级域名,二者连在一起)

"""
import re

with open('redata.txt', 'r') as f:
    i = 0
    while True:
        i += 1
        content = f.readline()
        m = re.search(r'::(.*@)(.+)::', content)

        if m is not None:
            print('第', i, '行电子邮件地址中提取出登录名和域名是', m.group(1), m.group(2))
        if not content:
            break
