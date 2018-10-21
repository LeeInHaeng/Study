a, b = map(int, input().strip().split(' '))
for x in range(0,b):
    tmp = ''
    for y in range(0,a):
        tmp+='*'
    print(tmp)