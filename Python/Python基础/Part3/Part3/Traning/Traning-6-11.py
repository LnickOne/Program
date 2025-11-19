#coding:utf-8

import os
def cleanfile(filename):
    print ("选择c: 创建一个新的 '清洁' 文件")
    print ('选择o: 覆盖原始的文件')
    op=input('请输入你的选择:')
    if op.lower()=='c':
        newfilename=input('请输入新的文件名:')
        ofile=open(filename,'r',encoding='GBK')
        dfile=open(newfilename,'w',encoding='GBK')
        oflines=map((lambda line:line.strip()),ofile) #去掉每行的空格
        
        #oflines=[line.strip() for line in ofile]   #该方法是列表解析法
               
        for line in oflines:
            dfile.write(line)
            dfile.write(os.linesep)

    elif op.lower()=='o':
        ofile=open(filename,'r',encoding='GBK')
        oflines=map((lambda line:line.strip()),ofile)
        #oflines=[line.strip() for line in ofile] #该方法是列表解析法,和map的效果一样
        
        #ofile.close()
        
        dfile=open(filename,'w',encoding='GBK')   #直接覆盖原来的文件
        #调试了很多次，依然无法直接覆盖，可能是边读边写的操作python3不适用？ ofile关了再打开也不行。此题作罢
        for line in oflines:
            dfile.write(line)
            dfile.write(os.linesep)
   
    else:
        print ('你没有选择c 或者o ,请重新输入')
   
    ofile.close()
    dfile.close()
cleanfile('test1.txt')
