def solution(skill, skill_trees):
    answer = 0
    for st in skill_trees:
        idx = 0
        status = True
        for s in st:
            if s in skill:
                if skill.index(s)==idx:
                    idx+=1
                else:
                    status = False
                    break
        if status==True:
            answer+=1
    return answer