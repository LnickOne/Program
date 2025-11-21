# coding:utf-8

import urllib
import urllib2
import cookielib
import re


def chou_url(hosturl, headers, number, posturl1, posturl2, restr):
    # 官方代码cookie
    cj = cookielib.LWPCookieJar()
    cookie_support = urllib2.HTTPCookieProcessor(cj)
    opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
    urllib2.install_opener(opener)
    h = urllib2.urlopen(hosturl)

    out_list = []
    for i in xrange(1, number):
        posturl = posturl1 + str(i) + posturl2
        req = urllib2.Request(posturl)
        for key in headers:
            req.add_header(key, headers[key])
        html = urllib2.urlopen(req).read()
        find = re.findall(restr, html)
        for item in find:
            x = item.find('"')
            if x > 0:
                out = item[:x]
            else:
                out = item
            out_list.append("item.jd.com" + out)
    return out_list

if __name__ == '__main__':

    hosturl = "https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page=1&sort=sort_rank_asc&trans=1&JL=6_0_0"
    headers = {
        'Host': 'list.jd.com',
        'Referer': 'https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page=3&sort=sort_rank_asc&trans=1&JL=6_0_0',
        'Upgrade-Insecure-Requests': 1,
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.90 Safari/537.36'
    }
    number = 5
    posturl1 = 'https://list.jd.com/list.html?cat=9987,653,655&ev=exprice%5FM2800L4499&page='
    posturl2 = '2&sort=sort_rank_asc&trans=1&JL=6_0_0'
    restr = 'href="//item.jd.com(.*?)" >'

    contents = chou_url(hosturl, headers, number, posturl1, posturl2, restr)
    for item in contents:
        print item
