#coding:utf-8
# 生成器法,生成器是一边计算一边返回
def FindIp(path):
    list1= []
    
    for line in open(path): 
        s = line.find("Mozilla/5.0" )
        s1=line.find("Sogou web spider/4.0")
        if s >0 :
            yield line[:s-1].strip()
        if s1 >0 :
            yield line[:s1-1].strip()        
if __name__ == '__main__':
    p = FindIp("ip.txt")
    p = sorted(list(set(list(p))))
    file2 = open("ipout-3.txt","w")
    for j in p:
        file2.write(j+"\n")     
    for item in p :
        print (item)
    file2.close()
        