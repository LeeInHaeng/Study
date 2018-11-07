from collections import defaultdict

def solution(genres, plays):
    dic = defaultdict(list)
    for x in range(0,len(genres)):
        dic[genres[x]].append([plays[x],x])
    for d in dic:
        dic[d] = sorted(dic[d],reverse=True)
    for d in dic:
        if len(dic[d])>1:
            for x in range(0,len(dic[d])-1):
                if dic[d][x][0]==dic[d][x+1][0]:
                    dic[d][x], dic[d][x+1] = dic[d][x+1], dic[d][x]
    bestGen = []
    for key,valList in dic.items():
        playCnt = 0
        for v in valList:
            playCnt+=v[0]
        tmp = [playCnt,key]
        bestGen.append(tmp)
    bestGen = sorted(bestGen,reverse=True)
    answer = []
    for b in bestGen:
        songCnt = 0
        for db in dic[b[1]]:
            answer.append(db[1])
            songCnt+=1
            if songCnt==2:
                break
    return answer