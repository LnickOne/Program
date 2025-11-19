# coding:utf-8
import urllib
import urllib.request
import re
import http.cookiejar

#hosturl = "http://www.baidu.com"
get_url = "https://www.baidu.com/s?wd=%E7%A7%91%E6%8A%80&rsv_spt=1&rsv_iqid=0xc0579e100002df61&issp=1&f=3&rsv_bp=0&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_enter=0&rsv_sug3=2&rsv_sug1=2&rsv_sug7=100&prefixsug=%25E7%25A7%2591%25E6%258A%2580&rsp=0&inputT=8262&rsv_sug4=8262"


# cj = http.cookiejar.LWPCookieJar()
# cookie_support = urllib.request.HTTPCookieProcessor(cj)
# opener = urllib.request.build_opener(
#     cookie_support, urllib.request.HTTPHandler)
# urllib.request.install_opener(opener)

# h = urllib.request.urlopen(hosturl)


headers = {
    'Cookie': 'BAIDUID = 4503F881A5E242790BE8DB1FF869D21D: FG = 1',
    'BIDUPSID': '4503F881A5E242790BE8DB1FF869D21D',
    'PSTM': 1536584531,
    'BD_UPN': 12314753,
    'BDUSS': '252ZkZZVWtQUTdGV0VVcFE3dmVuNmhYc0tCMDh0NDNjeEJOVGZ4TWo0OHhROEJiQUFBQUFBJCQAAAAAAAAAAAEAAACjRs0wd290ZWJpbWkAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADG2mFsxtphba',
    'BDORZ': 'B490B5EBF6F3CD402E515D22BCDA1598',
    'BD_HOME': 1,
    'H_PS_PSSID': '26524_1455_21084_26350_20928',
    'sugstore': 0,
    'BDRCVFR[feWj1Vr5u3D]': 'I67x6TjHwwYf0',
    'delPer': 0,
    'BD_CK_SAM': 1,
    'PSINO': 2,
    'H_PS_645EC': 'dbd9TQTgqVFlY % 2BT1Jw63eFiOF9RBqF4qIEHfIfb8M7zEzvjrt8HC2ptKLbnqMkgK3XTp',
    'BDSVRTM': 163,
    'Host': 'www.baidu.com',
    'Pragma': 'no-cache',
    'Upgrade-Insecure-Requests': 1,
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0Win64x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}


req = urllib.request.Request(get_url)
for key in headers:
    req.add_header(key, headers[key])
r = urllib.request.urlopen(req)
html = r.read()  # .decode('utf-8')

f = open('baidu.html', 'wb')
f.write(html)
f.close()

# findword = re.findall(r'2FDpC0Lr">(.*?)</a>', html)  # 这里是读字符串的方法
# print(findword)
