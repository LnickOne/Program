#coding:utf-8

file1 = open ("test.txt","r",encoding='utf-8')
file2 = open ("outputtest.txt","w",encoding='utf-8')

while 1 :
    line = file1.readline()
    
    s1 = line.find("*编号***")
    s2 = line.find("公司行业：")
    s3 = line.find("公司性质：")
    s4 = line.find("公司规模：")
    if s1 >0:
        file2.write(line)
        line = file1.readline()
        line = file1.readline()
        file2.write("公司名称: "+line)
    
    if s2>=0:
        file2.write(line[:s3]+"\n")
        file2.write(line[s3:s4]+"\n")
        file2.write(line[s4:])
    
        list1=[]
        
        while 1:
            line = file1.readline()
            s5 = line.find("**编号***")
            s6 = line.find("都国科海博")
            print("s5值为",s5)
            if s5 < 0:
                list1.append(line.strip())
            
            if s5 > 0:
                file2.write("公司简介: "+ "".join(list1)+"\n\n")
                file2.write(line)
                line = file1.readline()
                line = file1.readline()
                file2.write("公司名称: "+line)
                break
            if s6 > 0:
                list1.append(line)
                file2.write("公司简介: "+ "".join(list1)+"\n")                
                
            if not line:
                break
    if not line :
        break

file1.close()
file2.close()