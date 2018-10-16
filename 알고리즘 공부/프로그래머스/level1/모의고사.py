def solution(answers):
    answer = []
    cnt = [0,0,0]
    su = [[1,2,3,4,5],[2,1,2,3,2,4,2,5],[3,3,1,1,2,2,4,4,5,5]]
    ite = [0,0,0]
    
    for x in range(0,len(answers)):
        for y in range(0,3):
            if x>=len(su[y]) and x%len(su[y])==0:
                ite[y]+=len(su[y])
            if answers[x]==su[y][x-ite[y]]:
                cnt[y]+=1
    
    for x in range(0,3):
        if max(cnt)==cnt[x]:
            answer.append(x+1)
    return answer