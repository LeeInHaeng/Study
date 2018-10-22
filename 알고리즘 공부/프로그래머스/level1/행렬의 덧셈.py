def solution(arr1, arr2):
    answer = [[]]
    for c in range(0,len(arr1)):
        tmp = [arr1[c][r]+arr2[c][r] for r in range(0,len(arr1[c]))]
        answer.append(tmp)
    return answer[1:]