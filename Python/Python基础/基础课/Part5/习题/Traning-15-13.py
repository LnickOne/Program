# coding:utf-8
"""
写一个正则表达式，能从这个字符串中提取出类型的名字


"""
import re


def Extract(symbol):
    type1 = r"<type '\w*'>"
    m = re.match(type1, symbol)
    if m is not None:
        print(m.group())
    else:
        print('no any match')


if __name__ == '__main__':
    Extract("<type 'string'>")
