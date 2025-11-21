#coding:utf-8
# 函数法

file2 = open("ipout-2.txt","w")
def FindIp(path): 
    list1= []
    
    for line in open(path): 
        s = line.find("Mozilla/5.0" )
        s1=line.find("Sogou web spider/4.0")
        if s >=0:
            list1.append(line[:s-1].strip()) 
        if s1>=0:
            list1.append(line[:s1-1].strip())
  
    list2 = sorted(list(set(list1)))    
    return list2
    

    
    


if __name__ == '__main__':
    list2= FindIp("ip.txt")
    for j in list2:
        file2.write(j+"\n")    
    print (len(list2))
    print (list2)
    file2.close()
