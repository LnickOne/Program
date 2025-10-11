# coding:utf-8

import web

urls = (
    '/', 'index',
    '/test', 'Test'
)


class index:

    def GET(self):
        return "hello world"


class Test(object):

    def GET(self):
        return "你好ggpyweb"


if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
