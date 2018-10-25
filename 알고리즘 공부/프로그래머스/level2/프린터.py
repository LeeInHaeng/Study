from collections import deque

def solution(priorities, location):
    dic = {}
    for idx,val in enumerate(priorities):
        dic[idx] = val
    q_dic = deque(dic.items())
    answer = 0
    maxval = max(priorities)
    while True:
        if maxval!=q_dic[0][1]:
            q_dic.append(q_dic.popleft())
        else:
            idx,val = q_dic.popleft()
            answer += 1
            maxval = -1
            for qidx,qval in q_dic:
                if maxval<qval:
                    maxval = qval
            if location==idx:
                return answer