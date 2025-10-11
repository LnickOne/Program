# coding:utf-8
import MySQLdb as mdb
import sys

con = mdb.connect('localhost', 'root', '123456', 'webpy', charset="utf8")
with con:  # with可以自动关闭数据库连接
        # 获取连接的cursor,只有获取了cursor,我们才能进行各种操作
    cur = con.cursor()
    # 创建一个数据表 writers(id,name)
    # cur.execute("CREATE TABLE IF NOT EXISTS Writers(Id INT PRIMARY KEY AUTO_INCREMENT,Name VRRCHAR(25))")

    # 以下插入5条数据
    cur.execute("INSERT INTO study(dwmc, dz, tel, beizhu, jianjie) VALUES('中蓝公寓', '北京市朝阳区', '998', 'Zola', 'python study')")
    #cur.execute("INSERT INTO study(dwmc, dz, tel, beizhu, jianjie) VALUES('中蓝', '朝阳区', '122132321998', 'Lance', 'study')")
    # cur.execute("INSERT INTO study(dz) VALUES('北京市朝阳区')")
    # cur.execute("INSERT INTO study(tel) VALUES('998')")
    # cur.execute("INSERT INTO study(beizhu) VALUES('Zola')")
    # cur.execute("INSERT INTO study(jianjie) VALUES('python study')")
