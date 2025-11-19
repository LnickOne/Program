# coding:utf-8

import sys
sys.path.append(r"Users/manki/Desktop/Part5/")
import mymodule


def importAs(module):
    newname = __import__(module)
    return newname


newname = importAs('mymodule')
