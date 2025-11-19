# coding:utf-8
import urllib
import urllib2
import re
import time
import random

iplist = ['1.9.189.65:3128', '27.24.158.130:80']
list1 = ["集团", "科技"]
for item in list1:

    gjc = urllib2.quote(item)
    ip = random.choice(iplist)
    url = "https://sug.so.360.cn/suggest?callback=suggest_so&encodein=utf-8&encodeout=utf-8&word=" + gjc
    headers = {
        "GET": url,
        "Host": "sug.so.360.cn",
        "Referer": "https://www.so.com/",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36"
    }

    # 用代理ip以下三句话
    proxy_suppor = urllib2.ProxyHandler({'http': 'http://' + ip})

    opener = urllib2.build_opener(proxy_suppor)
    urllib2.install_opener(opener)

    req = urllib2.Request(url)  # 传这个example地址给这个request构造函数

    for key in headers:
        req.add_header(key, headers[key])
    html = urllib2.urlopen(req).read()
    a = re.findall("\"(.*?)\"", html)
    for i in a:
        print(i)
    # time.sleep(5)
