def solution(dirs):
    pos = [[0,0]]
    cur_pos = [0,0]
    res = []
    for d in dirs:
        tmp_pos = cur_pos.copy()
        if d=="U":
            if tmp_pos[1]<5:
                tmp_pos[1]+=1
                pos.append(tmp_pos)
        elif d=="D":
            if tmp_pos[1]>-5:
                tmp_pos[1]-=1
                pos.append(tmp_pos)
        elif d=="R":
            if tmp_pos[0]<5:
                tmp_pos[0]+=1
                pos.append(tmp_pos)
        elif d=="L":
            if tmp_pos[0]>-5:
                tmp_pos[0]-=1
                pos.append(tmp_pos)
        cur_pos = tmp_pos.copy()
    print(pos)
    for x in range(0,len(pos)-1):
        tmpList1 = []
        tmpList1.append(pos[x])
        tmpList1.append(pos[x+1])
        tmpList2 = []
        tmpList2.append(pos[x+1])
        tmpList2.append(pos[x])
        myChain1 = [y for k in tmpList1 for y in k]
        myChain2 = [y for k in tmpList2 for y in k]
        if myChain1 not in res and myChain2 not in res:
            res.append(myChain1)
    return len(res)