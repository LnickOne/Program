# coding:utf-8
import os
import os.path
import subprocess

print os.system("ls")

# f = os.popen("Part8")

# print f.read()

ret = subprocess.call("ls", shell=True)
print ret

p = subprocess.Popen("ls", shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
