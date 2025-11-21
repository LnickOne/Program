# coding:utf-8


def Modify_Open(filename, mode='r'):
    try:
        f = open(filename, mode)
    except Exception:
        return None
    else:
        return f


if __name__ == "__main__":
    print(Modify_Open('Test10-6.txt'))
