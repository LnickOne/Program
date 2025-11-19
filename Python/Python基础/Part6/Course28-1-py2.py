# coding:utf-8
import urllib
import urllib2
import re

html = urllib2.urlopen('http://www.so.com').read()
# print(html)

s = re.search("<title>(.*?)</title>", html)
print(s.group(1))
