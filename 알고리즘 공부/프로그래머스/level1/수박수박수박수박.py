def solution(n):
    answer = ''
    for x in range(0,n):
        if x%2==0:
            answer+='¼ö'
        else:
            answer+='¹Ú'
    return answer
