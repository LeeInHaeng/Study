def solution(d, budget):
    answer = 0
    for x in sorted(d):
        budget-=x
        answer+=1
        if budget<0:
            answer-=1
            break
    return answer