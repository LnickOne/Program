# coding:utf-8
"""
线程和文件
把练习 9-19 的答案做一些改进。我们要得到一个字节值,一个文件名然后显示在文件中那个字节出现了多少次。
假设这个文件非常的大。文件是可以有多个读者的,那我们就可以创建多个线程,每个线程负责文件的一部分。
最后,把所有的线程的结果相加。使用 timeit()对单线程和多线程分别进行计时,对性能的改进进行讨论。


9-19练习
创建文件. 
创建前一个问题的辅助程序. 创建一个随机字节的二进制数据文件, 但某一特定字节会在文件中出现指定的次数. 该程序接受三个参数:
1) 一个字节值( 0 - 255 ),
2) 该字符在数据文件中出现的次数, 以及
3) 数据文件的总字节长度.
你的工作就是生成这个文件, 把给定的字节随机散布在文件里, 并且要求保证给定字符在文件中只出现指定的次数
文件应精确地达到要求的长度.
"""
from random import randint


def create(filename, value, total, maxlen):
    assert 0 <= value <= 255
    ls = [chr(randint(0, 255)) for i in xrange(maxlen - total)]
    ch = chr(value)
    for i in xrange(total - ls.count(ch)):
        ls.insert(randint(0, len(ls) - 1), ch)
    for i in xrange(maxlen - len(ls)):
        ls.insert(randint(0, len(ls) - 1), chr(randint(0, value - 1)))
    with open(filename, 'wb') as f:
        f.write(''.join(ls))

if __name__ == '__main__':
    filename = raw_input('file name: ')
    value = int(raw_input('value: '))
    total = int(raw_input('total: '))
    maxlen = int(raw_input('max length of file: '))
    create(filename, value, total, maxlen)
