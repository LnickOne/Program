# coding:utf-8


import re

str = "an example word:cat!!"

match = re.search(r'word:\w\w\w', str)
ss= re.match(r'iii','piiig') #match必须从左到右找
ss = re.search(r'iii', 'siiig')#seach全局找
ss= re.search(r'\d\d\d','p123')
ss= re.search(r'\w\w\w','p123')

if match:
    print('found', match.group())
else:
    print("did not find")
if ss:
    print('found', ss.group())
else:
    print("did not find")
