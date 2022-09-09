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


int fileProcessCron(FILE *crontab, struct Crontab crontab_data[MAX_LEN]){
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
            strcpy(crontab_data[line].minute, cmd);
            line++;
        }

    }

}


int fileProcessEstimate(struct Estimate est_data[MAX_LEN], FILE *estimate){
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
            printf("%i is an invalid input", month);
            exit(EXIT_FAILURE);
    }
    return days;
}

int validDay(int month, int day){
    int maxDay = daysOfMonth(month);
    if (day>=0 && day <= maxDay){
        return 0;
    }
    else{
        printf("Invalid day provided for the month");
        exit(EXIT_FAILURE);
    }
}



void reportError(struct Crontab crontab_data[MAX_LEN], struct Estimate est_data[MAX_LEN]){
    int i = 0; // pointer to keep track of each command line in the structure

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

void estimatecron(char *month, FILE *crontab_file, FILE *estimates_file){
    int maxCommand = 0;
    int invokedCommand = 0;
    char all = '*'; //defining * to be all possible valid value


    char crontabData[MAX_LEN][MAX_CHAR];
    char estimateData[MAX_LEN][MAX_CHAR];
    int i = 0; //use to keep track of character in a line 


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


