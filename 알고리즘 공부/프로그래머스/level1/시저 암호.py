def solution(s, n):
    answer = ''
    for x in s:
        if x!=' ':
            if ord(x) >= 97 and ord(x) <= 122:
                if ord(x)+n>122:
                    answer += chr(ord(x)+n-26)
                else:
                    answer += chr(ord(x)+n)
            elif ord(x) >= 65 and ord(x) <= 90:
                if ord(x)+n>90:
                    answer += chr(ord(x)+n-26)
                else:
                    answer += chr(ord(x)+n)  
        else:
            answer+=' '
    return answer