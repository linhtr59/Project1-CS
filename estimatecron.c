// CITS2002 PROJECT 1 2022
// STUDENT 1: 23234683 TRINH LINH
// STUDENT 2: 23147438 NGUYEN THAI HOANG LONG

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_LEN 20
#define MAX_CHAR 100



struct Crontab{
    char minute[3];
    char hour[3];
    char day[3];
    char month[3];
    char date[3];
    char command[41];
};


struct Estimate{
    char command[41];
    char min[3];
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




int fileProcessCron(FILE *crontab, struct Crontab crontab_data[MAX_LEN]){
    int line = 0;//keeps track of every line in file and also act as pointer for struct idex
    int j = 0; //keeps track of the individual character in a line
    int file_size = 0;

    char lines[MAX_LEN];


    while(fgets(lines, sizeof lines, crontab)!= NULL){
        char cmin[3];
        char chour[3];
        char cday[3];
        char cmonth[4];
        char cdate[4];
        char cmd[41];

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
            file_size ++;
        }

    }
    return file_size;

}




int fileProcessEstimate( FILE *estimate, struct Estimate est_data[MAX_LEN]){
    int line = 0;//keeps track of every line in file and act as pointer for struct index
    int j = 0; //keeps track of the individual character in a line
    int file_size = 0;

    char lines[MAX_LEN];

    while(fgets(lines, sizeof lines, estimate)!= NULL){
        char cmd[41];
        char minute[3];
        


        while (isspace(lines[j])){ // if the character is a white space, continute to examine next character
            j ++;
        }

        if (lines[j] != '#'){ // if the first nons-space character is not a # then store data into struct 
            sscanf(lines, "%s,%s",
                          cmd, minute);
            strcpy(est_data[line].command, cmd);
            strcpy(est_data[line].min, minute); 
            line++;
            file_size ++;
        }

    }
    return file_size;

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
    int num = 0; 
    if((isnumber(*day))){ 
        if(atoi(day) < 7){
            num = atoi(day);// if it is already an int that is less than 7, return that
            return num;
        }

    }
    else{
        char *days[7] = {"mon", "tue", "wed", "thu", "fri", "sat","sun"};
        for(int i = 0; i < 7; i++){
        if((strcmp(days[i], day)) == 0){ // Compares whether given day is a valid day (or substring)
            num = i;
            return num;
        }
    }
    }
    
    fprintf(stderr, "Invalid input");
    exit(EXIT_FAILURE);
}





int monthToInt(char *month){
    //if given a string (jan-dec) convert that to a number
    int num; 
    if(isnumber(*month)){
        if(atoi(month) < 11){
            num = atoi(month);
            return num;
        }
    }
    else{
        const char *months[12] = {"jan", "feb", "mar","apr", "may", 
                            "jun","jul", "aug", "sep", "oct", "nov", "dec"};

        for(int i = 0; i < 12; i++){
        if(strcmp(months[i], month) == 0){ // Compares whether month match with any months array item
            num = i;
            return num;
        }
    }

    }
    fprintf(stderr, "Month is an invalid input");
    exit(EXIT_FAILURE);

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



void reportError(struct Crontab crontab_data[MAX_LEN], int cronSize){

    for (int i =0; i < cronSize ; i ++ ){
        //reporting errors on minute in crontab,  
        if (strcmp(crontab_data[i].minute, "*")!= 0){//if minute is not * -->
            if(atoi(crontab_data[i].minute) < 0 || atoi(crontab_data[i].minute) > 59){//check if its < 0 or > 59, if yes report error and exit 
                fprintf(stderr,"Minute provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting errors on hour in crontab
        if (strcmp(crontab_data[i].hour, "*")!= 0 ){//if hour is not * -->
            if(atoi(crontab_data[i].hour) < 0 || atoi(crontab_data[i].hour) > 23){//check if its <0 or > 23, if yes report error and exit
                fprintf(stderr,"Hour provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting errors on date in crontab
        if (strcmp(crontab_data[i].day, "*") !=0){ //if date is not * -->

            if(strcmp(crontab_data[i].month,"*") ==0){ // if month is equals to * report generic error
                if (atoi(crontab_data[i].day) < 0 || atoi(crontab_data[i].day) > 31 ){ // date < 0 or date > 31 then exit and report error
                    fprintf(stderr,"Date provided is out of scope");
                    exit(EXIT_FAILURE);

                }
            }
            else if (strcmp(crontab_data[i].month, "*") !=0){ // and if the month provided is also not * -->
                int currentMonth = monthToInt(crontab_data[i].month);
                int maxDay = daysOfMonth(currentMonth);
                //report error accordingly to the specified month
                if (atoi(crontab_data[i].day) < 0 || atoi(crontab_data[i].day) > maxDay ){ // if the date provided is < 0 or is larger than the max date for the provide month, report error and exit 
                    fprintf(stderr,"Date provided is out of scope");
                    exit(EXIT_FAILURE);
                }     
            }
        }



        //reporting errors on month in crontab
        if (strcmp(crontab_data[i].month, "*") !=0){ // if day is not * --> 
            int currentMonth = monthToInt(crontab_data[i].month);
            if (currentMonth < 0 || currentMonth > 11){ // if month is < 0 or > 11, report error and exit 
                fprintf(stderr,"Month provided is out of scope");
                exit(EXIT_FAILURE);
            }
        }


        //reporting erros on day in crontab
        if(strcmp(crontab_data[i].day, "*") !=0){ //if dayis not * -->
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
    int maxCommand = 0; //max command invoked at any particular time
    int invokedCommand = 0; //total invoked command in the month
    int nrunning = 0; // keeps track of the amount of command running while looping through every minute
    int cmdMonth = monthToInt(month);



    struct Crontab crontab_data[MAX_LEN];
    struct Estimate est_data[MAX_LEN];
    

    struct Process{
        char command[40];
        int time;
    }process[MAX_LEN];

    int estSize = fileProcessEstimate(estimates_file, est_data );
    int cronSize = fileProcessCron( crontab_file, crontab_data);
    reportError(crontab_data, cronSize);

    //iterate through every minute in the provided and month and log commands 
    int minInMonth = (60*24) * daysOfMonth(cmdMonth); //no of minutes in the given month
    for (int min = 0; min <= minInMonth; min++){
        for (int i =0; i < cronSize; i++){
            
            
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


