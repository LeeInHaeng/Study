def solution(num):
    if 'cnt' not in solution.__dict__:
        solution.cnt = 0
    if num==1:
        return 0
    if num%2==0:
        num = num/2
        solution.cnt+=1
        if solution.cnt>500:
            return -1
        if num==1:
            return solution.cnt
        else:
            return solution(num)
    else:
        num = num*3+1
        solution.cnt+=1
        if solution.cnt>500:
            return -1
        return solution(num)