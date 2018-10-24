def solution(arrangement):
    arrangement = arrangement.replace('()','x')
    stick = []
    cnt = 0
    for idx,val in enumerate(arrangement):
        if val=='(':
            stick.append(idx)
        elif val==')':
            tmp = arrangement[stick.pop():idx]
            cnt += (tmp.count('x')+1)
    return cnt