

'makeTextFile.py -- create text file '

import os
ls = os.linesep
fname = 'testfile'
# get filename

while True:

        if os.path.exists(fname):
                print ("ERROR :'%s' already exist" %fname)
        else:
                break

#get file content(text) lines
all = []
print("\nEnter lines ('.'by itself to quit). \n")

#loop until user terminates input
while True:
    entry = input('>')
    if entry !='.':
        all.append(entry)
    else:
        break

#write lines to file with proper line-ending
fobj = open(fname,'w')
fobj.writelines(['%s%s'% (x,ls) for x in all])
fobj.close()

print('done')