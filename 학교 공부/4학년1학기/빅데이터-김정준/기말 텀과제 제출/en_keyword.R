#install.packages("KoNLP")
#install.packages("rJava")
#install.packages("ggplot2")
# 41673개 데이터

library(KoNLP)
library(rJava)
library(ggplot2)
setwd('C:/Users/lih/Desktop/bigdata과제/DDOD논문목록')

# Data Load
df_source = read.csv(file="2000~2018해외논문.csv",header=TRUE,stringsAsFactors=FALSE)

# 컬럼명을 소문자로 변환
names(df_source) <- tolower(names(df_source))

wcYear <- 2017
idx <- 0
title <- list()

for(year in df_source$entrydate){
  if(year==wcYear){
    title <- append(title,list(df_source$title[idx]))
  }
  idx <- idx+1
}

# 단어 추출
nouns <- sapply(title,extractNoun,USE.NAMES=F)
#print(nouns[[1]][length(nouns[[1]])])

# 각 타이틀 마지막 단어 잘리는거 처리
for(idx in 1:length(nouns)){
  if(length(nouns[[idx]][length(nouns[[idx]])])==1){
    nouns[[idx]][length(nouns[[idx]])-1] <- paste0(nouns[[idx]][length(nouns[[idx]])-1],nouns[[idx]][length(nouns[[idx]])])
  }
}

write(unlist(nouns),paste(wcYear,"wc.txt"))
revised <- read.table(paste(wcYear,"wc.txt"))
revised <- tolower(readLines(paste(wcYear,"wc.txt")))

# filter

# and, for, the, with, using, from, through, towards
revised <- sub("and","",revised)
revised <- sub("for","",revised)
revised <- sub("the","",revised)
revised <- sub("with","",revised)
revised <- sub("using","",revised)
revised <- sub("from","",revised)
revised <- sub("through","",revised)
revised <- sub("towards","",revised)

#3글자 이상만
revised <- Filter(function(x){
  nchar(x)>=3
},revised)

merge_revised <- list()
one_revised <- list()

for(idx in 2:length(revised)-1)
  merge_revised <- append(merge_revised,list(paste(revised[idx],revised[idx+1])))
for(idx in 1:length(revised))
  one_revised <- append(one_revised,list(revised[idx]))

wordcount <- table(unlist(merge_revised))
wordcount2 <- table(unlist(one_revised))

res <- head(sort(wordcount,decreasing = T),20)
res_one <- head(sort(wordcount2,decreasing=T),20)

print(res)
print(res_one)

res <- data.frame(res)
pie(res$Freq,res$Var1,col=rainbow(10))