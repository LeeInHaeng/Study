def solution(a, b):
    sum=0
    if b>a:
        for x in range(a,b+1):
            sum+=x
    else:
        for x in range(b,a+1):
            sum+=x
    return sum