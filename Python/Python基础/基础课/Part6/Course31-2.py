# coding:utf-8

"""
修改用户名密码
http://bbs.chinaunix.net/member.php?mod=logging&action=login&logsubmit=yes
"""
import urllib
import urllib.request
import http.cookiejar

hosturl = "http://bbs.chinaunix.net/member.php?mod=logging&action=login&logsubmit=yes"
posturl = "http://bbs.chinaunix.net/member.php?mod=logging&action=login&loginsubmit=yes&loginhash=Le568"

# 官方代码cookie
cj = http.cookiejar.LWPCookieJar()
cookie_support = urllib.request.HTTPCookieProcessor(cj)
opener = urllib.request.build_opener(
    cookie_support, urllib.request.HTTPHandler)
urllib.request.install_opener(opener)
h = urllib.request.urlopen(hosturl)

headers = {

    'Host': 'bbs.chinaunix.net',
    'Origin': 'http://bbs.chinaunix.net',
    'Referer': 'http://bbs.chinaunix.net/member.php?mod=logging&action=login&logsubmit=yes',
    'Upgrade-Insecure-Requests': 1,
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}

# 如果用户名是汉字 rullib.quote
post_data = {
    'formhash': '2b4bb279',
    'referer': 'http://bbs.chinaunix.net/./',
    'username': u'python爱好者'.encode("gbk"),
    'password': '123456a',
    'loginsubmit': 'true',
    'return_type': ''
}
post_data = urllib.parse.urlencode(post_data)
print(post_data)

req = urllib.request.Request(posturl, post_data, headers)

f = urllib.request.urlopen(req)

html = f.read()  # .decode('utf-8')
f = open("testlogin.html", 'w')
f.write(html)
f.close()
