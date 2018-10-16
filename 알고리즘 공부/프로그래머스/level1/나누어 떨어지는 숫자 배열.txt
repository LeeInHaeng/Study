def solution(arr, divisor):
    tmp = sorted(list(filter(lambda a: a%divisor==0, arr)))
    if len(tmp)==0:
        tmp.append(-1)
        return tmp
    else:
        return tmp