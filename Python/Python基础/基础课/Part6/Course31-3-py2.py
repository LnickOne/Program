# coding:utf-8

"""
采集模块里的翻页

"""

import urllib
import urllib2
import cookielib
import re

#hosturl = "http://bbs.chinaunix.net/forum-55-1.html"
#posturl = 'http://bbs.chinaunix.net/forum-55-2.html'

# 官方代码cookie
cj = cookielib.LWPCookieJar()
cookie_support = urllib2.HTTPCookieProcessor(cj)
opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
urllib2.install_opener(opener)
#h = urllib2.urlopen(hosturl)

headers = {
    'Host': 'bbs.chinaunix.net',
    'Referer': 'http://bbs.chinaunix.net/forum-55-1.html',
    'Upgrade-Insecure-Requests': 1,
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.90 Safari/537.36'
}
#file2 = open("testfile.txt", 'w')
for i in xrange(1, 3, 1):
    posturl = 'http://bbs.chinaunix.net/forum-55-' + str(i) + '.html'
    req = urllib2.Request(posturl)
    for key in headers:
        req.add_header(key, headers[key])
    html = urllib2.urlopen(req).read()
    find = re.findall(r'<a href="(.*?)" onclick="atarget\(this\)', html)
    for item in find:
        x = item.find('"')
        if x > 0:
            out = item[:x]
        else:
            out = item
        print out
#         file2.write(out+'\n')
# file2.close()
