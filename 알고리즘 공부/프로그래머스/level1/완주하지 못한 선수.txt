def solution(participant, completion):
    idx = 0
    answer = ''
    if len(participant)<1 or len(participant)>100000:
        print("참가자의 수가 맞지 않음")
    else:
        if len(participant)-1 == len(completion):
            participant.sort()
            completion.sort()
            for x in range(0,len(completion)):
                idx = x
                if participant[x] != completion[x]:
                    answer = participant[x]
                    break
            if answer == '':
                return participant[idx+1]
            else:
                return answer
        else:
            print("완주한 사람의 수가 맞지 않음")