def solution(heights):
    answer = []
    tmp = []
    rlist = heights[::-1]
    for x in range(0,len(rlist)):
        for y in range(x+1,len(rlist)):
            if rlist[x]<rlist[y]:
                tmp.append(y)
                break
            if y==len(rlist)-1:
                tmp.append(0)
    tmp.append(0)
    for t in tmp:
        if t!=0:
            answer.append(len(heights)-t)
        else:
            answer.append(0)
    return answer[::-1]
