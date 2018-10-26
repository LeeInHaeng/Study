def solution(n, computers):
    graph = {}
    idx = -1
    for com in computers:
        idx += 1
        pathList = []
        for comidx,comval in enumerate(com):
            if idx!=comidx and comval==1:
                pathList.append(comidx)
        graph[idx]=set(pathList)
    res = [x for x in range(0,n)]
    answer = 0
    while True:
        visited = []
        stack = [res.pop(0)]
        while stack:
            num = stack.pop()
            if num not in visited:
                visited.append(num)
                stack+=graph[num]-set(visited)
        for v in visited:
            if v in res:
                res.remove(v)
        answer+=1
        if len(res)==0:
            return answer