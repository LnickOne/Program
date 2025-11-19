# coding:utf-8

"""
采集模块里的翻页

"""

import urllib
import urllib.request
import http.cookiejar
import re

s = '<a href="thread-4260522-1-10.html" onclick="atarget(this)" class="xst">如何训练自己的编程思路</a>'


hosturl = "http://bbs.chinaunix.net/forum-55-1.html"
#posturl = "http://bbs.chinaunix.net/forum-55-10.html"

# 官方代码cookie
cj = http.cookiejar.LWPCookieJar()
cookie_support = urllib.request.HTTPCookieProcessor(cj)
opener = urllib.request.build_opener(
    cookie_support, urllib.request.HTTPHandler)
urllib.request.install_opener(opener)
h = urllib.request.urlopen(hosturl)

headers = {
    'Host': 'bbs.chinaunix.net',
    'Referer': 'http://bbs.chinaunix.net/forum-55-1.html',
    'Upgrade-Insecure-Requests': 1,
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}
file1 = open("翻页测试.html", 'wb')
for i in range(1, 2):
    posturl = "http://bbs.chinaunix.net/forum-55-" + str(i) + ".html"

    req = urllib.request.Request(posturl)
    for key in headers:
        req.add_header(key, headers[key])
    html = urllib.request.urlopen(req).read()  # .decode('utf-8')
    file1.write(html)
    # find = re.findall(r'< a href="(.*?)" onclick="atarget\(this\)', html)
    # for item in find:
    #     x = item.find('"')
    #     if x > 0:
    #         out = item[:x]
    #     else:
    #         out = item
    #     file1.write(out.strip()+'\n')
file1.close()
