def solution(s):
    answer = ''
    for x in s.split(' '):
        for k in range(0,len(x)):
            if k%2==0:
                if x[k].islower():
                    answer += chr((ord(x[k])-32))
                else:
                    answer += x[k]
            else:
                if x[k].isupper():
                    answer += chr((ord(x[k])+32))
                else:
                    answer += x[k]
        answer += ' '
    return answer[:-1]