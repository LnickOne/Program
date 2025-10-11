# coding:utf-8


"""
将每行中的电子邮件地址替换为你自己的电子邮件地址。

"""
import re


with open('redata.txt', 'r') as f:

    while True:
        content = f.readline()
        m = re.match(r'(.*)::(.*)::(\d+)', content)
        if m is not None:
            a = m.group(2)
            a = 'huangge@python.com'
            print(a)
        if not content:
            break
