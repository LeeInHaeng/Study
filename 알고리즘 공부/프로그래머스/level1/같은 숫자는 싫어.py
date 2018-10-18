def solution(arr):
    res = []
    for x in range(0,len(arr)-1):
        if arr[x]^arr[x+1]:
            res.append(arr[x])
    res.append(arr[len(arr)-1])
    return res
