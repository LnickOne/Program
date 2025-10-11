# -*- coding: utf-8 -*-   
import math      

if __name__=='__main__':  
    ss = input()  
    ss = int (ss)
    print ('正方形面积：',ss*ss  )
    print ('立方体面积：',ss*ss*6)  
    print( '立方体体积：',ss*ss*ss  )
    print ('圆面积：',ss*ss*math.pi)  
    print ('球面积：',ss*ss*math.pi*4)  
    print ('球体积：',ss*ss*ss*math.pi*4/3.0)