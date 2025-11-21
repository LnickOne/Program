# coding:utf-8

import time


class ManagerDB(object):
    def __init__(self, ManagerDB):
        self.ManagerDB = ManagerDB

    # 注册用户名和密码
    def User(self):
        while True:
            UserName = input("输入注册的用户名:\n")

            if UserName in self.ManagerDB:
                print("你注册的用户名已经被占用")
                continue
            else:
                break
        UserPassword = input("输入该用户名密码:\n")

        self.ManagerDB[UserName] = []
        self.ManagerDB[UserName].append(UserPassword)

    # 时间戳
    def Time(self):
        LoginTime = time.time()
        for UserName in self.ManagerDB:
            self.ManagerDB[UserName].append(LoginTime)

    # 更新数据库方法(其实就是修改字典的键和值)
    def Update(self, UserName):

        while  True:
            NewUserName = input("输入你要变更的用户名:\n")
            if NewUserName in self.ManagerDB:
                print("你要修改的用户名已经存在数据库中")
                continue
            else:
                # 将原来该键的值赋给新的用户名
                self.ManagerDB[NewUserName] = self.ManagerDB[UserName]
                del self.ManagerDB[UserName]  # 删除旧键
                self.ManagerDB[NewUserName][0] = input("输入你要修改的密码:\n")
                self.WriteTxt()
                break

    # 写入磁盘txt文件
    def WriteTxt(self):
        f = open('AcconutInformation.txt', 'w')
        for key in self.ManagerDB:
            user = '用户名: ' + key + ' ' + '密码: ' + ' ' + \
                self.ManagerDB[key][0] + ' ' + '登录日期  ' + ':' + \
                str(time.ctime(self.ManagerDB[key][1])) + '\n'
            f.write(user)
        f.close()

    # 登录后访问 添加和更新数据库
    def Login(self):
        error = 3

        while error:
            UserName = input("登录名： ")
            UserPassword = input("密码: ")

            if UserName in self.ManagerDB:
                if UserPassword == self.ManagerDB[UserName][0]:
                    print("登录成功")
                    self.Time()
                    print("本次登录时间为", time.ctime(self.ManagerDB[UserName][1]))
                else:
                    print("密码错误")
                    error -= 1

            if error == 0:
                print("错误次数过多，已经退出系统")
            answer = input("你要修改自己的用户信息吗？y/n\n")[0].lower()
            if answer == 'y':
                self.Update(UserName)

            else:
                break


User = ManagerDB({})
User.User()
# User.User()
User.Login()
