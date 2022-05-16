# Fibonacci series:
# the sum of two elements defines the next
def fib(n):
    a = 0
    b = 1
    list = []
    while a < n:
        list.append(a)
        old_a = a
        a = b
        b = old_a + b
    return list
