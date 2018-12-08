install.packages('KoNLP')
install.packages('wordcloud')
install.packages('RColorBrewer')
install.packages("ggplot2")
install.packages("plotrix")

library(KoNLP)
library(wordcloud)
library(RColorBrewer)
library(ggplot2)
library(plotrix)

options(encoding="UTF-8") #텍스트 파일 읽을시에 한글 깨짐 방지

# 파일 읽기
fileIn_2000=file("kr_2000_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2001=file("kr_2001_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2002=file("kr_2002_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2003=file("kr_2003_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2004=file("kr_2004_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2005=file("kr_2005_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2006=file("kr_2006_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2007=file("kr_2007_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2008=file("kr_2008_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2009=file("kr_2009_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2010=file("kr_2010_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2011=file("kr_2011_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2012=file("kr_2012_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2013=file("kr_2013_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2014=file("kr_2014_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2015=file("kr_2015_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2016=file("kr_2016_keyword(test).csv",open="rb",encoding="UTF-8")
fileIn_2017=file("kr_2017_keyword(test).csv",open="rb",encoding="UTF-8")


lines = readLines(fileIn_2016)

#head(lines)
#View(lines)

# 프레임의 형태로 만들기
lines <- data.frame(lines)


#데이터 처리
lines$lines <- gsub(" ","",lines$lines) # 띄어쓰기 제거
lines$lines <- tolower(lines$lines) #소문자로 만들기

##########################################################################
#2015
lines$lines <- gsub("빅데이터","bigdata",lines$lines) # 빅데이터
lines$lines <- gsub("사물인터넷","iot",lines$lines) # 사물 인터넷
lines$lines <- gsub("iot(iot)","iot",lines$lines) # 사물 인터넷
lines$lines <- gsub("iot\\(iot\\))","iot",lines$lines) # 사물 인터넷

lines$lines <- gsub("internetofthings","iot",lines$lines) # 사물 인터넷
lines$lines <- gsub("스마트폰","smartphone",lines$lines) # 스마트폰
lines$lines <- gsub("안드로이드","android",lines$lines) # 안드로이드
lines$lines <- gsub("맵리듀스","mapreduce",lines$lines) # 맵리듀스
lines$lines <- gsub("기계학습","machinelearning",lines$lines) # 기계학습
lines$lines <- gsub("하둡","hadoop",lines$lines) # 빅데이터
#2000

#2001

#2002
lines$lines <- gsub("xml-ql","xml",lines$lines) #xml
lines$lines <- gsub("xmldocument","xml",lines$lines) #xml
lines$lines <- gsub("유전알고리즘(ga)","geneticalgorithm",lines$lines) #xml

#2003

#2004
lines$lines <- gsub("neuralnetworks","neuralnetwork",lines$lines) # 신경망
lines$lines <- gsub("신경망","neuralnetwork",lines$lines)
lines$lines <- gsub("유전자알고리즘","geneticalgorithm",lines$lines)
lines$lines <- gsub("유전알고리즘","geneticalgorithm",lines$lines)
lines$lines <- gsub("유전적프로그래밍","geneticalgorithm",lines$lines)

#2006
lines$lines <- gsub("유비쿼터스","ubiquitous",lines$lines)
lines$lines <- gsub("온톨로지","ontology",lines$lines)

#2007
lines$lines <- gsub("센서네트워크","sensornetwork",lines$lines)

#2008
lines$lines <- gsub("wirelesssensornetworks","wirelesssensornetwork",lines$lines)

#2009
lines$lines <- gsub("무선센서네트워크","wirelesssensornetwork",lines$lines)
lines$lines <- gsub("무선sensornetwork","wirelesssensornetwork",lines$lines)
lines$lines <- gsub("wirelesssensornetworks","wirelesssensornetwork",lines$lines)
lines$lines <- gsub("데이터마이닝","datamining",lines$lines)
lines$lines <- gsub("영상처리","imageprocessing",lines$lines)

#2010
lines$lines <- gsub("클러스터링","clustering",lines$lines)

#2011
lines$lines <- gsub("서비스품질","qos",lines$lines)
lines$lines <- gsub("추천시스템","recommendation",lines$lines)
lines$lines <- gsub("위치기반서비스","locationbasedservice",lines$lines)
lines$lines <- gsub("인증","authentication",lines$lines)

#2012
lines$lines <- gsub("클라우드컴퓨팅","cloudcomputing",lines$lines)
lines$lines <- gsub("증강현실","augmentedreality",lines$lines)
lines$lines <- gsub("소셜네트워크서비스","socialnetworkservice",lines$lines)

#2013
lines$lines <- gsub("얼굴인식","facerecognition",lines$lines)
lines$lines <- gsub("블루투스","bluetooth",lines$lines)

#2014
lines$lines <- gsub("텍스트마이닝","textmining",lines$lines)

#2015
lines$lines <- gsub("의사결정나무","decisiontree",lines$lines)

#2016
lines$lines <- gsub("딥러닝","deeplearning",lines$lines)
lines$lines <- gsub("가상현실","virtualreality",lines$lines)

#2017
lines$lines <- gsub("드론","drone",lines$lines)
lines$lines <- gsub("인공지능","artificialintelligence",lines$lines)
lines$lines <- gsub("리눅스","linux",lines$lines)
lines$lines <- gsub("인공neuralnetwork","artificialneuralnetwork",lines$lines)
lines$lines <- gsub("임베디드시스템","embeddedsystem",lines$lines)
lines$lines <- gsub("라즈베리파이","raspberrypi",lines$lines)
lines$lines <- gsub("데이터베이스","database",lines$lines)
lines$lines <- gsub("스마트워치","smartwatch",lines$lines)
lines$lines <- gsub("머신러닝","machinelearning",lines$lines)
lines$lines <- gsub("로지스틱회귀분석","logisticregressionanalysis",lines$lines)
lines$lines <- gsub("아두이노","arduino",lines$lines)
lines$lines <- gsub("클라우드","cloudcomputing",lines$lines)
lines$lines <- gsub("회귀분석","regressionanalysis",lines$lines)


#관련 단어가 있는 키워드 추출하기
#len = length(grep("fuzzy",lines$lines))
#len

##############################################################################
#갯수 새기
y <- table(lines)
y <- data.frame(y)

#head(y)
#정렬하기
y <- y[order(y$Freq,decreasing = TRUE),]

#top 20 뽑기 
y <- y[1:20,]
#y
colnames(y) =c("keyword","freq")
#############################################################################
#관련 단어 모두 합치기
for(i in 1:20){
  y[i,2] <- length(grep(y[i,1],lines$lines))
}
y <- y[order(y$freq,decreasing = TRUE),]
#############################################################################

#top 10 뽑기 
#y <- y[1:10,]
#그래프 그리기 - pie graph
pie(y$freq,y$keyword,col = rainbow(10))

#3차원 그래프
#pie3D(y$freq,labels=y$keyword)
