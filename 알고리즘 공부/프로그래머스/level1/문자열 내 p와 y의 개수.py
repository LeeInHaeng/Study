def solution(s):
    p_cnt = y_cnt = 0

    for x in s.lower():
        if x=='p':
            p_cnt+=1
        if x=='y':
            y_cnt+=1
    return p_cnt==y_cnt
