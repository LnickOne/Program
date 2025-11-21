# coding:utf-8
import urllib
import urllib2
import re
import chardet

"""
1.访问网页的基本编码
"""

html = urllib2.urlopen("http://www.yahoo.com").read()
mychar = chardet.detect(html)  # 侦测这个网站用的是啥编码格式
# print mychar
code = mychar['encoding']
print(code)
if code == 'utf-8' or code == 'UTF-8':
    out_html = html
elif code == 'gb2312' or code == 'GBK' or code == 'GB2312':
    out_html = html.decode('gbk', 'ignore').encode('utf-8')  # 先将gb2312编码的html字符串转换成unicode,再将unicode的html转换为utf-8编码
# print out_html
