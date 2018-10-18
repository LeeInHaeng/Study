def solution(array, commands):
    answer=[sorted(array[i[0]-1:i[1]])[i[2]-1] for i in commands]        
    return answer
