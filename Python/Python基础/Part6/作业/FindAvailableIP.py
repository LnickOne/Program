# coding:utf-8
import urllib
import urllib2
import cookielib
import re


def FindFanYe():
    hosturl = "https://www.youdaili.net/Daili/http/list_1.html"

    # 官方代码cookie
    # cj = cookielib.LWPCookieJar()
    # cookie_support = urllib2.HTTPCookieProcessor(cj)
    # opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
    # urllib2.install_opener(opener)
    # h = urllib2.urlopen(hosturl)
    YeMianXuHao = []
    for i in xrange(1, 2):
        headers = {
            'Referer': 'https://www.youdaili.net/',
            'Upgrade-Insecure-Requests': 1,
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
        }
        posturl = 'https://www.youdaili.net/Daili/http/list_' + str(i) + '.html'
        req = urllib2.Request(posturl)
        for key in headers:
            req.add_header(key, headers[key])
        html = urllib2.urlopen(req).read()
        find = list(set(re.findall(r'<a href="https://www.youdaili.net/Daili/http/(.*?)".*target', html)))
        for item in find:
            x = item.find('.html')
            if x > 0:
                out = item[:x]
            else:
                out = item
            YeMianXuHao.append(out)
    # print len(YeMianXuHao)
    return YeMianXuHao


def CollectIP():
    ip_list = []
    file1 = open('ip.txt', 'w')
    for i in FindFanYe():
        hosturl1 = 'https://www.youdaili.net/Daili/http/' + str(i) + '.html'

        headers1 = {
            #'Host': 'https://www.youdaili.net/Daili/http/',
            'Referer': hosturl1,
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'

        }
        req = urllib2.Request(hosturl1)
        for key in headers1:
            req.add_header(key, headers1[key])
        html = urllib2.urlopen(req).read()

        ip = list(set(re.findall('p>(.*?)@HTTP#', html)))  # |">(.*?)@SOCKS4
        for j in ip:
            #j = list(j)
            # if j[1] != '':
            #     continue
            # print j
            # for i in j:
            a = j.find("p")
            if a > 0:
                ip_list.append(j[a + 2:])
            file1.write(j[a + 2:] + '\n')
    file1.close()
    print ip_list


def main():
    for i in FindFanYe():
        print i
    CollectIP()
if __name__ == '__main__':
    main()
