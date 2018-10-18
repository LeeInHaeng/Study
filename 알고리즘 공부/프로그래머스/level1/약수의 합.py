def solution(n):
    if n==0:
        return 0
    elif n==1:
        return 1
    else:
        res = [1,n]
        for x in range(2,n):
            if n%x==0:
                res.append(x)
        return sum(res)
