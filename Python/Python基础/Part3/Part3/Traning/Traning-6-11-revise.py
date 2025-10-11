#coding:utf-8


#问题1
def WriteNewFile():
    print ("你选择了c直接清洁")
    OldContent = ReadFile()
    newfilename=input('请输入新的文件名:')
    NewContent=list(map((lambda line:line.strip()),OldContent)) #去掉每行的空格，并且赋值给一个变量，这个变量得到去掉空格后的内容
    file2=open(newfilename,'w')
    for line in NewContent:
        file2.write(line+'\n')
    print('写入成功')
    file2.close()        

#问题2
def CoveredFile():
    print("你选择了o覆盖原文件")
    OldContent = ReadFile()
    #NewContent=list(map((lambda line:line.strip()),OldContent))
    NewContent=[line.strip() for line in OldContent] #该方法是列表解析法,和map的效果一样
    #print (NewContent) #用来测试写入内容
    
    file2 = open('test1.txt','w') 
    for line in NewContent:
        file2.write(line+'\n')    
    
    print('覆盖成功')
    file2.close()    
    
def ReadFile():
    with open("test1.txt",'r') as file1:
        content = file1.readlines()
    file1.close()
    return content
        

#汇总:
def main():
    print("请输入你的选择'c'或者'o':")
    option = input()
    if option.lower() == "c":
        WriteNewFile() 
    elif option.lower() == "o":
        CoveredFile()
    else:
        print("没有适合的指令，请重新输入")


#主程序入口
if __name__ == '__main__':
    main()
