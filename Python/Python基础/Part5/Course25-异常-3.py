# coding:utf-8


def foo1():
    x = 1
    y = x / 0


def foo2():

    f = open("ww.txt")


if __name__ == "__main__":
    try:
        foo1()
        foo2()

    except ZeroDivisionError as e:
    	print (e)

    except Exception as e:
        print(e)

