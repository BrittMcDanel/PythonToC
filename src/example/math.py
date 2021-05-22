def add(a, b):
    return a + b


def loop_func(size):
    for i in range(size):
        print("loop var", i)


def main():
    int_value = add(5, 10)
    double_value = add(5.0, 10.0)
    print("values", int_value, double_value)
    loop_func(20)
