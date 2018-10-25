def solution(phone_book):
    tmp = [len(p) for p in phone_book]
    for x in range(0,len(phone_book)):
        for y in range(0,len(phone_book)):
            if x!=y and phone_book[x]==phone_book[y][:tmp[x]]:
                return False
    return True
