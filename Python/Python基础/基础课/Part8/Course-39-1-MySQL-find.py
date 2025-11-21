# coding:utf-8
import MySQLdb as mdb


con = mdb.connect('localhost', 'root', '123456', 'webpy', charset="utf8")
with con:  # with可以自动关闭数据库连接
        # 获取连接的cursor,只有获取了cursor,我们才能进行各种操作
    cur = con.cursor()
    cur.execute("select * from study where dz like '%朝阳%'")

    rows = cur.fetchall()  # 使用fetchall函数,将结果(多维元组)存入rows里面
    for row in rows:
        print row[0], row[1].encode("utf-8"), row[2].encode("utf-8"), row[3].encode("utf-8"), row[4].encode("utf-8"), row[5].encode("utf-8")
