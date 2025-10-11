# coding:utf-8

"""
采集手机信息页

"""

import urllib
import urllib2
import cookielib
import re

hosturl = "https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page=1&sort=sort_rank_asc&trans=1&JL=6_0_0"

# 官方代码cookie
cj = cookielib.LWPCookieJar()
cookie_support = urllib2.HTTPCookieProcessor(cj)
opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
urllib2.install_opener(opener)
h = urllib2.urlopen(hosturl)

headers = {
    'Host': 'list.jd.com',
    'Referer': 'https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page=3&sort=sort_rank_asc&trans=1&JL=6_0_0',
    'Upgrade-Insecure-Requests': 1,
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.90 Safari/537.36'

}

out_list = []
for i in xrange(1, 5):
    posturl = 'https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page=' + str(i) + '2&sort=sort_rank_asc&trans=1&JL=6_0_0'
    req = urllib2.Request(posturl)
    for key in headers:
        req.add_header(key, headers[key])
    html = urllib2.urlopen(req).read()
    find = re.findall(r'href="//item.jd.com(.*?)" >', html)
    for item in find:
        x = item.find('"')
        if x > 0:
            out = item[:x]
        else:
            out = item
        out_list.append("item.jd.com" + out)
for item in out_list:
    print item
    # html = urllib2.urlopen(item).read()#.decode("gbk").encode('utf-8')
    # txt = re.findall(r'<div id="postlist" class="pl bm">(.*?)<div class="tip_horn"></div>', html, re.S)  # re.S是换行的意思
    # for item in txt:  # txt是一个列表
    #     item = re.sub(r'<[\/\!]*?[^<>]*?|<script[^>]*?>.*?</script>si|window.zlzp=window.zlzp||{};|&(nbsp|#160);|&(quot|#34);|" target="_blank">(.*)</a>', '', item)  # sub是替换
    #     item = re.sub(r'\n\s*\r|     |document.getElementById(.*);|<span class="rz">(.*)</span>]</span>|<a href="|   | ', '', item)
    #     item = re.sub(r'&nbsp;|&gt:&gt;', '   ', item)
