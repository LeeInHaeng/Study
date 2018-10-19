def solution(x, n):
    if x==0: return [0 for k in range(0,n)]
    return [k for k in range(x,x*n+1,x)] if x>0 else [k for k in range(x,x*n-1,x)]
