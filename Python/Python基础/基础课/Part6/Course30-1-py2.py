# coding:utf-8
import urllib
import urllib2
import re
import cookielib

hosturl = "http://www.baidu.com"
get_url = "https://www.baidu.com/s?ie=utf-8&mod=1&isbd=1&isid=D10F44141CE12213&ie=utf-8&f=8&rsv_bp=0&rsv_idx=1&tn=baidu&wd=%E7%A7%91%E6%8A%80&rsv_pq=f2c56db40005589e&rsv_t=4e67o7vy6B5DqDKw%2FHqumzdLo2K1Q7f%2Fz6SKRgvKwdBBUBj47%2BXMwk%2F%2FPbY&rqlang=cn&rsv_enter=0&rsv_sug3=5&rsv_sug1=2&rsv_sug7=100&inputT=3390&rsv_sug4=4280&rsv_sid=1428_21109_20927&_ss=1&clist=&hsug=&f4s=1&csor=2&_cr1=27656"


cj = cookielib.LWPCookieJar()
cookie_support = urllib2.HTTPCookieProcessor(cj)
opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)
urllib2.install_opener(opener)
h = urllib2.urlopen(hosturl)


headers = {
    'Host': 'www.baidu.com',
    'is_referer': 'https://www.baidu.com/',
    'is_xhr': 1,
    'Referer': 'https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=0&rsv_idx=1&tn=baidu&wd=%E7%A7%91%E6%8A%80&rsv_pq=f2c56db40005589e&rsv_t=4e67o7vy6B5DqDKw%2FHqumzdLo2K1Q7f%2Fz6SKRgvKwdBBUBj47%2BXMwk%2F%2FPbY&rqlang=cn&rsv_enter=0&rsv_sug3=5&rsv_sug1=2&rsv_sug7=100&inputT=3390&rsv_sug4=4280',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}

req = urllib2.Request(get_url)
for key in headers:
    req.add_header(key, headers[key])
r = urllib2.urlopen(req)
html = r.read()

# f = open('baidu.html', 'w')
# f.write(html)

findword = re.findall(r'rs_src=0(.*?)</a>', html)

for i in findword:
    a = i.find(">")
    if a > 0:
        i = i[a + 1:]
        print i
# f.close()
