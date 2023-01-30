#Data incubator: Data challenge
#Sanaz Rabinia Haratbar, January 29, 2023
library ("stringr")
library(dplyr)
library(reshape2)
rm(list = ls())
getwd()
setwd("C:/Users/sanaz/OneDrive/Documents/R-Udemy/Data_incubator")


#-----------------------Question 1.1-------------------------------------------
data <- read.csv("nyc_noise_complaints.csv", header = TRUE)
nycpopulation = read.csv("nycpopulation.csv", header = TRUE)
print('Number of rows')
numberOfRows <- (nrow(data))
print("Number of rows: ")
print(numberOfRows)


#-----------------------Question 1.2-------------------------------------------
musicNoise <- data[str_detect(data$descriptor, "Music"),]
numberOfRowsOfMusicNoise <- (nrow(musicNoise))
fractionOfMusicNoise <- numberOfRowsOfMusicNoise/ numberOfRows
print ("fraction of noise complaints deal with music: ")
print (fractionOfMusicNoise)




#-----------------------Question 1.3-------------------------------------------
df_22 <- data[str_detect(data$created_date, "2022"), ]
df_MANHATTAN <- df_22[df_22$borough=="MANHATTAN",]
df_MANHATTAN_closed <- df_MANHATTAN[df_MANHATTAN$status=="Closed",] 
closed_cases <- (nrow(df_MANHATTAN_closed))
probability <- (closed_cases/(nrow(df_MANHATTAN)))
print("Probability of a complaint's status is "Closed" given that it happened in Manhattan: ")
print (probability)


#double check with groupby
df_MANHATTAN %>% 
  group_by(status) %>%
  summarise(count = n())

#-----------------------Question 1.4-------------------------------------------
data$noise_complain <- ifelse(str_detect(data$descriptor, "Construction"),'construction_related','not_related')
df_zip <- data%>% 
  group_by(incident_zip,noise_complain) %>%
  summarise(count_rec = n())


valid_zips <-subset(df_zip, noise_complain == "construction_related" & count_rec > 100)

list_valid_zip <- unique(valid_zips$incident_zip)

df_valid = filter(df_zip,
                  incident_zip %in% list_valid_zip)

df_valid_reshape <- dcast(df_valid, incident_zip ~ noise_complain,
                          value.var = "count_rec",
                          na.rm=False)

df_valid_reshape$total_comp <- df_valid_reshape$construction_related+df_valid_reshape$not_related
df_valid_reshape$construction_related_fraction <- df_valid_reshape$construction_related/df_valid_reshape$total_comp

print("Standard Deviation: ") 
print(sd(df_valid_reshape$construction_related_fraction)) 

#-----------------------Question 1.5-------------------------------------------
df_zip_pop <- data%>% 
  group_by(incident_zip) %>%
  summarise(count_rec = n())

mergedData <- merge(df_zip_pop, nycpopulation, by.x=c('incident_zip'),by.y=c('ZIP_CODE'))
relation <- lm(mergedData$count_rec~mergedData$POPULATION)
print(summary(relation))
plot(mergedData$POPULATION,mergedData$count_rec,
     main='Regression for Complains and Population',
     xlab='Population',ylab='Complains')
abline(lm(mergedData$count_rec~mergedData$POPULATION),col='red')
print("slope of a line of best fit: ")
relation$coefficients
