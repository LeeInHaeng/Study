def solution(n, m):
    answer = []
    yak = []
    if n<m:
        for x in range(1,n+1):
            if n%x==0 and m%x==0:
                yak.append(x)
        answer.append(max(yak))
    elif n>m:
        for x in range(1,m+1):
            if n%x==0 and m%x==0:
                yak.append(x)
        answer.append(max(yak))
    else:
        answer.append(n)
    answer.append(answer[0]*(n/answer[0])*(m/answer[0]))
    return answer
