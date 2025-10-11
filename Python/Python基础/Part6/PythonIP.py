# coding:utf-8
import requests
import bs4


class SpiderProxy(object):
    """黄哥Python培训 黄哥所写 Python版本为2.7以上"""
    headers = {
        "Host": "www.xicidaili.com",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36",
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
        'Accept-Encoding': 'gzip, deflate',
        'Accept-Language': 'zh-CN,zh;q=0.9',
        "Referer": "http://www.xicidaili.com/wt/1",
    }

    def __init__(self, session_url):
        self.req = requests.session()
        self.req.get(session_url)

    def get_pagesource(self, url):
        html = self.req.get(url, headers=self.headers)
        return html.content

    def get_all_proxy(self, url, n):
        data = []
        for i in range(1, n):
            html = self.get_pagesource(url + str(i))
            soup = bs4.BeautifulSoup(html, "lxml")

            table = soup.find('table', id="ip_list")
            for row in table.findAll("tr"):
                cells = row.findAll("td")
                tmp = []
                for item in cells:

                    tmp.append(item.find(text=True))
                data.append(tmp[1:3])
        return data

session_url = 'http://www.xicidaili.com/wt/1'
url = 'http://www.xicidaili.com/wt/'
p = SpiderProxy(session_url)
proxy_ip = p.get_all_proxy(url, 10)
for item in proxy_ip:
    if item:
        print item
