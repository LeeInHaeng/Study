import threading
import random
import time

customCnt = int(input("전체 고객의 수를 입력하세요 : "))
bank = int(input("은행 창구의 수를 입력하세요 : "))
sem = threading.Semaphore(bank)      # 세마포 객체 생성, ~개의 쓰레드로 제한

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

customs = []

start_time = time.time()
for i in range(customCnt): # ~개수의 쓰레드
        customs.append(RestrictedArea())
        print(customs[i].getName().replace("Thread","Custom")+" 번호표 뽑음")

for cus in customs:
        cus.start()          # 쓰레드 시작

for cus in customs:
        cus.join()           # 종료대기
        print(cus.getName().replace("Thread","Custom")+" 퇴장\n")
end_time = time.time()

print('%d 명의 고객 상담 완료' % (i+1))
print('총 상담 처리 시간 : %lf초' % (end_time - start_time))
