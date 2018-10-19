def solution(n):
    _sum = 0
    for i in [x for x in str(n)]:
        _sum += int(i)
    return _sum