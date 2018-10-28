def solution(begin, target, words):
    answer = []
    def dfs(start,wlist,path):
        sim = []
        for w in wlist:
            cnt = 0
            for x in range(0,len(start)):
                if start[x]==w[x]:
                    cnt+=1
                    if cnt==len(start)-1:
                        sim.append(w)
        if target in sim:
            answer.append(path)
            return
        else:
            path+=1
            for s in sim:
                wlist_copy = wlist.copy()
                wlist_copy.remove(s)
                dfs(s,wlist_copy,path)
    dfs(begin,words,1)
    if len(answer)==0:
        return 0
    else:
        return min(answer)
