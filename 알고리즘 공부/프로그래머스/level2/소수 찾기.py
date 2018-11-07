def solution(numbers):
    answer = 0
    resNum = []
    def dfs(strNum,extraNum):
        for e in extraNum:
            resNum.append(int(strNum+e))
            exceptIndex = extraNum.index(e)
            dfs(strNum+e,extraNum[:exceptIndex]+extraNum[exceptIndex+1:])
    dfs('',numbers)
    resNum = set(resNum)
    print(resNum)

    for r in resNum:
        status = True
        if r<2:
            status=False
        else:
            for x in range(2,r):
                if r%x==0:
                    status = False
                    break
        if status==True:
            answer+=1
    return answer