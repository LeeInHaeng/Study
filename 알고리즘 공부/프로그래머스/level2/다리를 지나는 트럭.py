from collections import deque

def solution(bridge_length, weight, truck_weights):
    t = 0
    timer,passT = [],[]
    ingT = deque()
    truck_weights = deque(truck_weights)
    origin_len = len(truck_weights)
    while True:
        t+=1
        if len(timer)!=0:
            timer = [x+1 for x in timer]
        for idx,tt in enumerate(timer):
            if tt==bridge_length+1:
                passT.append(ingT.popleft())
                timer = timer[1:]
        if len(truck_weights)!=0:
            if sum(ingT)+truck_weights[0]<=weight:
                ingT.append(truck_weights.popleft())
                timer.append(1)
        if len(passT)==origin_len:
            break
    return t