
###############################################################################
        #IT 업계의 논문 동향 키워드 분석#

# -*- coding:utf-8 -*-

import requests
import bs4
import time
import numpy as np

class Crawling:
    def __init__(self,page):
        self.page=page
        self.cur_page=page
        
        save_file = open('test('+str(self.page)+'~).txt',mode='w',encoding='utf8')
        try:      
            print('[*] 크롤링 Start')
            s1 = requests.session()
            headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.181 Safari/537.36'}

            #9733
            for page in range(self.page,9000):
                self.cur_page = page
#                x= np.random.randint(5,10)
                s1 = requests.session()
                print("page : ",page)
                page_url = "https://www.dbpia.co.kr/SearchResult/Search?q=%28%5B%EB%85%BC%EB%AC%B8%C2%A7coldb%C2%A72%C2%A751%C2%A73%5D%29&searchWord=%EC%A0%84%EC%B2%B4%3D%5E%24%EB%85%BC%EB%AC%B8%5E*&Collection=0&nSort=1&nSorttype=desc&Page="+str(page)+"&nPagesize=20&fCategory=76%5E_ND08%5E_%EC%A0%84%EC%9E%90%2F%EC%A0%95%EB%B3%B4%ED%86%B5%EC%8B%A0%2F%EC%BB%B4%ED%93%A8%ED%84%B0%EA%B3%B5%ED%95%99&searchAll=%EB%85%BC%EB%AC%B8&Multimedia=0&isFullText=0&Collection=0&SearchMethod=0&PublishDate=&PublishSttDate=&PublishEndDate="
                req_page = s1.get(page_url,headers=headers)
            
                soup = bs4.BeautifulSoup(req_page.text,'html.parser')
                        
                tags_title = soup('a')
            
                for tag_title in tags_title:
            
                    tag_title_class = tag_title.get('href')
                    #print(str(tag_title_class)[:22])
                    if str(tag_title_class)[:22] == '/Journal/ArticleDetail':
                        #print(tag_title_class)
#                        x= np.random.randint(7,12)
#                        time.sleep(x)
                        full_url = "https://www.dbpia.co.kr"+tag_title_class
                        
                        response = requests.get(full_url,headers=headers)
                        html = response.text
                        soup = bs4.BeautifulSoup(html,'html.parser')
                        
                        if soup.find('h3') is not None:
                            print(soup.find('h3').text) # 논문 제목
                            save_file.write(soup.find('h3').text+",")
                        
                        if soup.find('dt') is not None: 
                            #print(soup.find('dt').text) # 논문 날짜 
                            temp = soup.find('dt').text
                            date = temp.split(",")[1]
                        
            #            print(date.split('.')[0].strip())
                            save_file.write(date.split('.')[0].strip()+",")
                        
                        for tag in soup.find_all('a'):
                        #    print(type(tag.get('class')))
                            if tag.get('class') is not None and 'keyword' in tag.get('class') :
                        
                                temp = tag.text[1:]
            #                    print(temp) # 키워드 
                                save_file.write(temp+",")
                        
                        
                        save_file.write("\n")
            #            print(full_url)
        except:
            save_file.close()
            print('----------Connection Aborted!! Crawling Restart--------------')
            Crawling(self.cur_page+1)
        finally:
            save_file.close()

Crawling(8847)