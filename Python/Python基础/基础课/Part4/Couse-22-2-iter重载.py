# coding:utf-8


class Foo(object):
    def __init__(self, data):
        self.data = data

    def __iter__(self):
        return self

    def next(self):
        for item in self.data:
            return item

        if not self.data:
            raise (StopIteration)


# list1 = [5, 6, 7, 8, 9]
# p = Foo(list1)
# print(type(p))
# for item in p:
#     print(item)
print (Foo)