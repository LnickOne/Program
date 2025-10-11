# coding:utf-8

import urllib
import urllib2
import cookielib
import re
import Course33py2


def Phone_Price(url_list):
    list1 = []

    for i in url_list:
        a = i.find("/")
        if a > 0:
            list1.append(i[a + 1:].strip('.html'))

    headers2 = {}
    for item in list1:
        url = "https://c0.3.cn/stock?skuId=" + item + "&area=1_72_2799_0&venderId=659959&cat=9987,653,655&buyNum=1&choseSuitSkuIds=&extraParam={%22originid%22:%221%22}&ch=1&fqsp=0&pduid=15385502660841903443508&pdpin=&detailedAdd=null&callback=jQuery857528"

        headers2 = {
            'DNT': 1,
            'Host': 'c0.3.cn',
            #'Referer': 'https://item.jd.com/32101310669.html',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:62.0) Gecko/20100101 Firefox/62.0',
        }
        new = urllib2.Request(url)
        for key in headers2:
            new.add_header(key, headers2[key])
        r = urllib2.urlopen(new, timeout=40).read().decode('gbk').encode('utf-8')
        m = re.search('"p":"(.+?)"', r)
        print m.group()[4:].strip(",")


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

contents = Course33py2.chou_url(hosturl, headers, number, posturl1, posturl2, restr)
Phone_Price(contents)
