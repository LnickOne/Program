# coding:utf-8
import urllib
import urllib2
import re
import cookielib
import random
import time

"""
讲前面第30讲的代码,重构为类.
支持代理访问,支持自动cookie
"""


class Baidu(object):
	"""
	类有两个方法,第一个方法:取html,第二:正则抽取相关搜索的内容
	"""

    def __init__(self, keyword, ip_list):
        headers = {
            'DNT': 1,
            'Host': 'www.baidu.com',
            'Referer': 'http://www.baidu.com',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
        }
        # 实例属性
        self.headers = headers
        self.keyword = keyword
        self.ip_list = ip_list

    def get_html(self, url):
    	# 第一个方法:取html
        hosturl = "http://www.baidu.com"
        ip = random.choice(self.ip_list)
        try:
            cj = cookielib.LWPCookieJar()
            cookie_support = urllib2.HTTPCookieProcessor(cj)
            proxy_support = urllib2.ProxyHandler({'hppt': 'http://' + ip})
            opener = urllib2.build_opener(cookie_support, proxy_support, urllib2.HTTPHandler)
            urllib2.install_opener(opener)
            h = urllib2.urlopen(hosturl)

            headers = {
                'DNT': 1,
                'Host': 'www.baidu.com',
                'Referer': 'http://www.baidu.com',
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
            }
            req = urllib2.Request(url)
            for key in self.headers:
                req.add_header(key, self.headers[key])
            r = urllib2.urlopen(req)
            html = r.read()
        except Exception as e:
            print e
        return html

    def get_word(self, html):
    	# 第二:正则抽取相关搜索的内容
        findword = re.findall(r'rs_src=0(.*?)</a>', html)
        wordlist = []
        for i in findword:
            a = i.find(">")
            if a > 0:
                i = i[a + 1:]
                wordlist.append(i)
        return wordlist


keyword_list = ["科技", "集团"]
for item in keyword_list:
    line = urllib.quote(item)
    ip_list = ['14.18.16.70:80', '47.93.4.104:80', '163.125.251.244:8118' '14.18.17.162:80', '60.161.14.77:8001']
    get_url = "https://www.baidu.com/s?wd=" + line + "&rsv_bp=0&rsv_spt=3&ie=utf-8&rsv_sug3=4&rsv_sug=0&rsv_sug1=4&rsv_sug4=45&inputT=17491"

    caiji = Baidu(line, ip_list)
    out_html = caiji.get_html(get_url)
    out_word = caiji.get_word(out_html)
    for item in out_word:
        print item
    time.sleep(3)
