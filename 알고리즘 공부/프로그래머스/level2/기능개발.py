def solution(progresses, speeds):
    answer = [1]
    tmp = [int((100-val)/speeds[idx]) for idx,val in enumerate(progresses)]
    c = tmp[0]
    idx = 0
    for x in range(1,len(tmp)):
        if c>=tmp[x]:
            answer[idx]+=1
        else:
            idx+=1
            c = tmp[x]
            answer.append(1)
    return answer
