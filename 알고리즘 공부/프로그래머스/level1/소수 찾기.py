def solution(n):
    # 에라토스테네스의 체
    res = [True]*(n+1)
    for x in range(2,len(res)):
        if res[x]==True:
            for k in range(x+x,len(res),x):
                res[k] = False
    tmp = [i for i in range(2, len(res)) if res[i] == True]
    return len(tmp)
