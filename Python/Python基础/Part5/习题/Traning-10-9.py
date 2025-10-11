# coding:utf-8

import math
import cmath


def safe_sqrt(x):
    try:
        num = math.sqrt(x)
    except Exception:
        num = cmath.sqrt(x)
    return num


if __name__ == '__main__':
    x = float(input('输入一个负数\n'))
    print(safe_sqrt(x))
