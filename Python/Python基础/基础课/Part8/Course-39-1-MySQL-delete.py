# coding:utf-8
import MySQLdb as mdb


con = mdb.connect('localhost', 'root', '123456', 'webpy', charset="utf8")
with con:  # with可以自动关闭数据库连接
        # 获取连接的cursor,只有获取了cursor,我们才能进行各种操作
    cur = con.cursor()
    cur.execute("delete  from study where dz like '%朝阳%'")
