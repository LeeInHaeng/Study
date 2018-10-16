def solution(n, lost, reserve):
    c = []
    for x in range(0,n):
        c.append(1)
    for l in lost:
        c[l-1]-=1
    for r in reserve:
        c[r-1]+=1

    for x in range(0,n):
        if c[x]==2:
            # ³¡ Ã³¸®
            if x==0 and c[1]==0:
                c[0] -= 1
                c[1] += 1
                state = 'start'
            elif x==n-1 and c[n-2]==0:
                c[n-1] -= 1
                c[n-2] += 1
                state = 'end'
            else:
                if x!=0 and x!=n-1:
                    if c[x-1]==0:
                        c[x]-=1
                        c[x-1]+=1
                    if c[x+1]==0:
                        c[x]-=1
                        c[x+1]+=1
    cnt = 0
    for x in c:
        if x>0:
            cnt += 1
    return cnt