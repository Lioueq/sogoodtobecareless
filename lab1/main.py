import sys

def f(c):
    return int(c, 16)

def radix_sort(a):
    for p in range(15, -1, -1):
        buckets = [0 for i in range(16)]
        for i in a:
            buckets[f(i[0][p])] += 1
        prefix = [0 for i in range(16)]
        prefix[0] = buckets[0]
        for i in range(1, 16):
            prefix[i] = prefix[i - 1] + buckets[i]

        for i in range(len(a) - 1, -1, -1):
            idx = f(a[i][0][p])
            a[prefix[idx] - 1], a[i] = a[i], a[prefix[idx] - 1]
            prefix[f(a[i][0][p])] -= 1

    return a

a = []
for i in sys.stdin:
    key, value = i.split()
    a += [(key, value)]

a = radix_sort(a)

for i in a:
    print(i[0], i[1])
