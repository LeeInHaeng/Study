def solution(numbers, target):
    res = []
    def dfs(start,idx):
        tidx = idx+1
        if tidx==len(numbers):
            res.append(start+numbers[idx])
            res.append(start-numbers[idx])
            return
        dfs(start+numbers[idx],tidx)
        dfs(start-numbers[idx],tidx)
    dfs(0,0)
    return res.count(target)