def solution(brown, red):
    recRed = []
    if red==1:
        return [3,3]
    for w in range(red,0,-1):
        if red%w==0:
            tmp = [w,int(red/w)]
            recRed.append(tmp)
    for r in recRed:
        if r[0]<r[1]:
            recRed = recRed[:recRed.index(r)]
            break
    for r in recRed:
        wCnt = r[0]*2
        hCnt = r[1]*2
        if wCnt+hCnt+4==brown:
            return [r[0]+2,r[1]+2]