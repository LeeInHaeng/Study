def solution(n):
    tmp = [str(n)[x] for x in range(len(str(n))-1,-1,-1)]
    return [int(t) for t in tmp]
