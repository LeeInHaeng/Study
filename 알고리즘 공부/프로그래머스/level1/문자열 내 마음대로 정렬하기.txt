from collections import defaultdict

def solution(strings, n):
    dic = defaultdict(list)
    for s in strings:
        dic[s[n]].append(s)
    res = []
    for x in list(map(lambda d: dic[d],list(sorted(dic.keys())))):
        tmp = sorted(x)
        for k in tmp:
            res.append(k)
    return res
