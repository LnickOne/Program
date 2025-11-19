#coding:utf-8

try: #try 是检测的意思,有可能出现问题的代码
	x = 1
	y = 1/0
	print ("1/0是不对的")
# except ZeroDivisionError as e: #出现异常就跳到这
# 	print ("分母不能为0")
# 	print ("%s"%(e,))

except Exception as e:
	print ("continue to excute code")

finally :
	print ("你上面有没有上面这段代码都得执行")