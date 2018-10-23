def solution(inputN):
    maxi = 0
    i = 0
    # suma 까지의 십진수 = i 비트
    while inputN>maxi:
        i+=1
        maxi+=3**i

    returnN = []

    for j in range(1,i+1):
        #temp1 = 3**j
        #temp2 = inputN % (3**j)
        tmp = inputN % (3**j)
        #print(tmp)

        if tmp == 0 :
            returnN.append('4')
        elif 1<=tmp and tmp<=(3**j)/3 :
            returnN.append('1')
        elif (3**j)/3<tmp and tmp<=(3**j)*2/3:
            returnN.append('2')
        else:
            returnN.append('4')

        #returnN.append(inputN%3**j)
        #print(returnN)
        inputN = inputN - 3**j

    return ''.join([r for r in returnN[::-1]])