// CITS2002 PROJECT 1 2022
// STUDENT 1: 23234683 TRINH LINH
// STUDENT 2: 23147438 NGUYEN THAI HOANG LONG

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20
#define MAX_CHAR 100
#define ANY '*'


struct Crontab{
    char minute[2];
    char hour[2];
    char day[2];
    char month[3];
    char date[3];
    char command[40];
};


struct Estimate{
    char command[40];
    int min;
};



FILE *openfile(char filename[]) {
    // If file is able to be opened, return the opened file 

    FILE *files = fopen(filename, "r");
    if(files == NULL) {
        fprintf(stderr, "File does not exist or cannot be opened '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(files);
    return files;
}




void fileProcessCron(FILE *crontab, struct Crontab crontab_data[MAX_LEN]){
    int line = 0;//keeps track of every line in file and also act as pointer for struct idex
    int j = 0; //keeps track of the individual character in a line

    char lines[MAX_LEN];


    while(fgets(lines, sizeof lines, crontab)!= NULL){
        char cmin[2];
        char chour[2];
        char cday[2];
        char cmonth[3];
        char cdate[3];
        char cmd[40];

        while (isspace(lines[j])){ // if the character is a white space, continute to examine next character
            j ++;
        }

        if (lines[j] != '#'){ // if the first nons-space character is not a # then store data into struct 
            sscanf(lines, "%s,%s,%s,%s,%s,%s",
                         cmin, chour, cday, cmonth, cdate, cmd);
            strcpy(crontab_data[line].minute, cmin);
            strcpy(crontab_data[line].hour, chour);
            strcpy(crontab_data[line].day, cday);
            strcpy(crontab_data[line].month, cmonth);
            strcpy(crontab_data[line].date, cdate);
            strcpy(crontab_data[line].command, cmd);
            line++;
        }

    }

}




void fileProcessEstimate(struct Estimate est_data[MAX_LEN], FILE *estimate){
    int line = 0;//keeps track of every line in file and act as pointer for struct index
    int j = 0; //keeps track of the individual character in a line

    char lines[MAX_LEN];

    while(fgets(lines, sizeof lines, estimate)!= NULL){
        char cmd[40];
        int minute = 0;

        while (isspace(lines[j])){ // if the character is a white space, continute to examine next character
            j ++;
        }

        if (lines[j] != '#'){ // if the first nons-space character is not a # then store data into struct 
            sscanf(lines, "%s,%i",
                          cmd, minute);
            strcpy(est_data[line].command, cmd);
            est_data[line].min = minute; 
            line++;
        }

    }

}





int daysOfMonth(int month){
    // returns max number of days in month;
    int days;
    switch(month){
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            days = 31;
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            days = 30;
            break;
        case 1:
            days = 28;
            break;
        default:
            fprintf(stderr,"%i is an invalid input", month);
            exit(EXIT_FAILURE);
    }
    return days;
}





int dayToInt(char *day){
    //if given a string (mon-sun) convert that to a number
    int num; 
    int check = atoi(day);
    if(!(isdigit(check))){ 
        num = check;// if it is already an int, return that
    }

    const char *days[7] = {"mon", "tue", "wed",
                             "thu", "fri", "sat","sun"};

    for(int i = 0; i < 7; i++){
        if(strcmp(days[i], day) ==0){ //Compares whether day match with any day array item 
            num = i;
        }
    }
    return num;
}





int monthToInt(char *month){
    //if given a string (jan-dec) convert that to a number
    int num; 
    int check = atoi(month);
    if(!(isdigit(check))){ 
        num = check;// if it is already an int, return that
    }

    const char *months[12] = {"jan", "feb", "mar","apr", "may", 
                            "jun","jul", "aug", "sep", "oct", "nov", "dec"};

    for(int i = 0; i < 12; i++){
        if(strcmp(months[i], month) == 0){ // Compares whether month match with any months array item
            num = i;
        }
    }
    return num;

}
   



int validDay(int month, int day){
    int maxDay = daysOfMonth(month);
    if (day>=0 && day <= maxDay){
        return 0;
    }
    else{
        fprintf(stderr,"Invalid day provided for the month");
        exit(EXIT_FAILURE);
    }
}





void reportError(struct Crontab crontab_data[MAX_LEN]){
//GETTING SOME WARNINGS HERE WITH COMPARING ANY TO THE DATA BUT MAYBE ITS FINE??? ALSO SIZEOF IS SOMEHTIMES INACCURATE, ASKED Q ON HELP FORUM, WILL GET BACK TO FIX THIS
    for (int i =0; i < sizeof crontab_data; i ++ ){
        //reporting errors on minute in crontab,  
        if (strcmp(crontab_data[i].minute, ANY)!= 0 ){//if minute is not * -->
            if(atoi(crontab_data[i].minute) < 0 || atoi(crontab_data[i].minute) > 59){//check if its < 0 or > 59, if yes report error and exit 
                fprintf(stderr,"Minute provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting errors on hour in crontab
        if (strcmp(crontab_data[i].hour, ANY)!= 0 ){//if hour is not * -->
            if(atoi(crontab_data[i].hour) < 0 || atoi(crontab_data[i].hour) > 23){//check if its <0 or > 23, if yes report error and exit
                fprintf(stderr,"Hour provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting errors on date in crontab
        if (strcmp(crontab_data[i].date, ANY) !=0){ //if date is not * -->

            if(strcmp(crontab_data[i].month, ANY) ==0){ // if month is equals to * report generic error
                if (atoi(crontab_data[i].date) < 0 || atoi(crontab_data[i].date > 31)){ // date < 0 or date > 31 then exit and report error
                    fprintf(stderr,"Date provided is out of scope");
                    exit(EXIT_FAILURE);

                }
            }
            else if (strcmp(crontab_data[i].month, ANY) !=0){ // and if the month provided is also not * -->
                int currentMonth = monthToInt(crontab_data[i].month);
                int currentDate = dayToInt(crontab_data[i].date);
                //report error accordingly to the specified month
                if (currentDate < 0 || (validDay != 0)){ // if the date provided is < 0 or is larger than the max date for the provide month, report error and exit 
                    fprintf(stderr,"Date provided is out of scope");
                    exit(EXIT_FAILURE);
                }     
            }
        }



        //reporting errors on month in crontab
        if (strcmp(crontab_data[i].month, ANY) !=0){ // if day is not * --> 
            int currentMonth = monthToInt(crontab_data[i].month);
            if (currentMonth < 0 || currentMonth > 11){ // if month is < 0 or > 11, report error and exit 
                fprintf(stderr,"Month provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting erros on day in crontab
        if(strcmp(crontab_data[i].day, ANY) !=0){ //if dayis not * -->
            int currentDay = dayToInt(crontab_data[i].month);
            if (currentDay < 0 || currentDay > 6){ // if day is < 0 or > 6, report error and exit 
                fprintf(stderr,"Day provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }
    }

// we will need to work on dayToInt and monthToInt in order to return negative number if the string provided doesnt match with any acceptable month/day
}


void estimatecron(char *month, FILE *crontab_file, FILE *estimates_file){
    int maxCommand = 0;
    int invokedCommand = 0;
    int nrunning = 0; //keeps track of no of process running at a given minute 
    int cmdMonth = monthToInt(month);

    struct Crontab crontab_data[MAX_LEN];
    struct Estimate est_data[MAX_LEN];
    

    struct Process{
        char command[40];
        int time;
    }process[MAX_LEN];

    fileProcessEstimate(est_data, estimates_file);
    fileProcessCron(crontab_data, crontab_file);
    reportError(crontab_data);

    //iterate through every minute in the provided and month and log commands 
    int minInMonth = (60*24) * daysOfMonth(cmdMonth); //no of minutes in the given month
    for (int min = 0; min <= minInMonth; min++){
        for (int i =0; i < sizeof crontab_data; i++){
// iterate through crontab lines and if the day & month and date and hour and min match approrpiately then do something
// *** needs to somehow be able to determine if a process start in this minute then incremen nrunning if a process terminate then decrement nrunning         
   *** at any one point nrunning become greater than maxCommand, update maxCommand
   *** also need too somehow keep track of the most frequently invoked commands 
   
        }

    }



}


int main(int argc, char *argv[]){
    if (argc != 4){
        printf("4 arguments required");
        exit(EXIT_FAILURE);
    }
    char *month =  argv[1];
    FILE *crontab = openfile(argv[2]);
    FILE *estimate = openfile(argv[3]);

    estimatecron(month, crontab, estimate);
}


