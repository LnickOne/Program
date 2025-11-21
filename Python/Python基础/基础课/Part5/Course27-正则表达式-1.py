# coding:utf-8

"""
re.search(pat,str,re.IGNORECASE)
IGNORECASE 不区分大小写a,即匹配a,又匹配A
DOTALL 允许.匹配\n
MULTILINE 在一个多行组成的字符串中，允许^与$匹配行的开始和结束
match
seach
findall
sub
split
"""
import re

#str1 = "hkyy jk Ahbrr98 njuy6\n Ah7778\n"
# str1 ='<b>foo</b> and <i> so on</i>'
#ss = re.findall('A.*?8',str1,re.DOTALL)
#ss = re.findall('A.*?8',str1,re.DOTALL) #非贪婪加个? 号，表示会取到后面的8
# ss =re.findall('<(.*?)>',str1) #加个？就是离大于号<最近的弄出来
# ss1 =re.search('<(.*?)>',str1) #search 找出最近的一个
# if ss:
# 	print (ss)
# if ss1:
# 	print (ss1.group())

str = 'sss b jk    b kkiib jklliub98'
ss = re.findall(r'b\s+|\d+',str)
# print (re.sub(r'b\s*',r'B',str))
# print (re.split(r'b\s*',str))
if ss:
	print (ss)