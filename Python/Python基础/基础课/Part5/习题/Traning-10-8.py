# coding:utf-8


def safe_input():
    try:
        p1 = input('输入一个参数,将会进行异常检查\n')
    except (EOFError, KeyboardInterrupt):

        return None
    else:
        return ("该输入没有异常", p1)


if __name__ == '__main__':
    print(safe_input())
