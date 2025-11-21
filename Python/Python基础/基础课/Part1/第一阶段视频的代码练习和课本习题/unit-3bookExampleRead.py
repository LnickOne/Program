# coding:utf-8
'Read testfile ---read and display'
# get filename
fname = input('输入读取的文件名称\n')

print(" ")

# attempt to open file for reading
try:
    fobj = open (fname,'r')
except (IOError,e):
   print("file open error: ",e)  #有错的话这样处理
#无错误的话就展示文件内容
else :
    #display contents to the screen
    for eachLine in fobj:
        print (eachLine.strip())
    fobj.close()

