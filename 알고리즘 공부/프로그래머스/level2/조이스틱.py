def solution(name):
    cnt = 0
    rMove, lMove = 0, 0
    change = [False]*len(name)
    for idx,n in enumerate(name):
        if n!="A":
            change[idx]=True
    for x in range(1,len(change)):
        if True in change[x:]:
            rMove+=1
    tchange = change[1:][::-1]
    for x in range(0,len(tchange)):
        if True in tchange[x:]:
            lMove+=1
    if rMove>=lMove:
        cnt+=lMove
    else:
        cnt+=rMove

    for n in name:
        if n<='M':
            cnt+=(ord(n)-65)
        else:
            cnt+=(91-ord(n))
    return cnt