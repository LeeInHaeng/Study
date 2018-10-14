import threading
import random
import time

customCnt = int(input("전체 고객의 수를 입력하세요 : "))
bank = int(input("은행 창구의 수를 입력하세요 : "))
sem = threading.Semaphore(bank)      # 세마포 객체 생성, ~개의 쓰레드로 제한
vip_sem = threading.Semaphore(1)

class RestrictedArea(threading.Thread):
        def run(self):
            # self.getName() : Thread-1, Thread-2 ....
            custom = self.getName().replace("Thread","Custom")
            CounselingTime = random.randint(5,10) # 작업소요시간 5~10초 사이
            
            msg =('[-]%s 상담중...\n' % custom)
            msg2 = ('[+]%s 상담 완료... / 상담 소요시간 : %d초\n' % (custom,CounselingTime))
                    
            sem.acquire()       # unlocked --> locked
            print(msg)                  # 쓰레드만이 존재할수 있는 영역
            time.sleep(CounselingTime)
            sem.release()       # locked --> unlocked
            print(msg2)

class RestrictedAreaVIP(threading.Thread):
        def run(self):
            # self.getName() : Thread-1, Thread-2 ....
            vip = self.getName().replace("Thread","[[ VIP ]]")
            CounselingTime = random.randint(5,10) # 작업소요시간 5~10초 사이
            
            msg =('[[[ [-]%s 상담중... ]]]\n' % vip)
            msg2 = ('[[[ [+]%s 상담 완료... / 상담 소요시간 : %d초 ]]]\n' % (vip,CounselingTime))
                    
            vip_sem.acquire()       # unlocked --> locked
            print(msg)                  # 쓰레드만이 존재할수 있는 영역
            time.sleep(CounselingTime)
            vip_sem.release()       # locked --> unlocked
            print(msg2)
            
vipSecond = 0
vipCnt = 0
def vipCreate():
        vips = []
        global vipCnt
        global vipSecond
        global proEnd
        while proEnd:
                vipSecond += 1
                time.sleep(1)
                if vipSecond%10==0:
                        print('[[[ VIP 등장! ]]]\n')
                        vips.append(RestrictedAreaVIP())
                        vips[vipCnt].start()
                        vipCnt+=1
        for vip in vips:
                vip.join()
        print('%d 명의 [ VIP ] 상담 완료' % (vipCnt))
                        
customs = []

proEnd = True
start_time = time.time()
for i in range(customCnt): # ~개수의 쓰레드
        customs.append(RestrictedArea())
        print(customs[i].getName().replace("Thread","Custom")+" 번호표 뽑음")

th = threading.Thread(target=vipCreate)
th.start()

for cus in customs:
        cus.start()          # 쓰레드 시작

for cus in customs:
        cus.join()           # 종료대기
        print(cus.getName().replace("Thread","Custom")+" 퇴장\n")
end_time = time.time()
proEnd = False

print('%d 명의 고객 상담 완료' % (i+1))
print('총 상담 처리 시간 : %lf초' % (end_time - start_time))
