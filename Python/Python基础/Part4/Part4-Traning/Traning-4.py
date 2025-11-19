# coding:utf-8

import time
class DBMnagement(object):
    '数据库管理类'

    def __init__(self, nm, pwd):
        self.name = nm
        self.password = pwd

    def updatePWD(self, newpwd):
        self.password = newpwd

    def __del__(self):
        pass





def CreateLog(username):
    '登陆成功写时间戳到log文件'
    timeStamp = time.ctime(time.time())
    log = 'User' + ' - ' + username + ', last time login Succeed at ' + timeStamp + '\n'
    logFile = open('LoginTest.txt', 'a')
    logFile.write(log)
    logFile.close()


def ReadLog():
    '登陆成功，从log文件读取上次时间戳'
    logFile = open('LoginTest.txt')
    logInfo = logFile.readlines()
    if len(logInfo) >= 1:
        print (logInfo[-1])
    logFile.close()


def ChangePWDinLog(username, newpwd):
    '修改用户密码'
    credentialFile = open('LoginTest.txt', 'w')
    credentialtxt = username + ' ' + newpwd
    credentialFile.write(credentialtxt)
    credentialFile.close()
    print('密码已修改 ... Password updated successfully. \n')


# 从这里开始是主程序
print('欢迎使用最简单的用户管理系统')
print('尝试用系统中已经存在的用户名和密码登录，有三次机会')
print('登陆成功后输入 updatepwd 命令可以修改密码，成功后退出系统')
print('登陆成功后输入 quit 命令退出系统\n')

credentialFile = open('LoginTest.txt')  # 从文本文件中获取用户名和密码
credentialInfo = credentialFile.readlines()
credentialFile.close()

# 这里credentialInfo[-1]是一个字符串，包括用户名和口令，空格隔开的
usernameinDB = credentialInfo[-1].split()[0]
passwordindm = credentialInfo[-1].split()[1]

errorTimes = 3
while errorTimes:
    print('请输入用户名和密码：')
    input_username = input('Username ... :  ')
    input_password = input('Password ... :  ')
    if input_username == usernameinDB and input_password == passwordindm:
        print('登陆成功  ... Login Successful')
        CurrentUser = DBMnagement(input_username, input_password)
        ReadLog()
        CreateLog(input_username)
        input_command = input('请输入你的命令, quit or updatepwd ... \n')
        if input_command == 'quit':
            del (CurrentUser)
            print('\n已退出系统  ... Logout successfully.')
            break
        elif input_command == 'updatepwd':
            newpwd = input('\n请输入新密码, new password ... :  ')
            CurrentUser.updatePWD(newpwd)
            ChangePWDinLog(CurrentUser.name, CurrentUser.password)
            del CurrentUser
            print('\n已退出系统  ... Logout successfully.')
            break
        else:
            print('错误命令  ... Wrong Command')
            del CurrentUser
            print('\n已退出系统  ... Logout successfully.')
            break
    else:
        print('用户名或口令错误  ... Wrong Username or Password.\n')
        errorTimes -= 1
        if errorTimes == 0:
            print('已退出系统  ... Logout successfully.')
