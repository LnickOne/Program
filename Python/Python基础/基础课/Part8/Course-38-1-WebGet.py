# coding:utf-8

import web

urls = (

    '/page?', 'foo2',
    '/hello/(.*)', 'foo1',  # 第二个参数是匹配的类
    r'/topic/(\d+)', 'foo3',
)


class foo1:

    def GET(self, name):
        return "hello ,from foo1" + name


class foo2(object):

    def GET(self):
        i = web.input(id=None)
        return "hello ,from foo2" + i.id


class foo3(object):

    def GET(self, id):
        id = int(id)
        return "需要的id =%d" % (id,)


if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
