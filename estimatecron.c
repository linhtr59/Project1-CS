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
#define MAX_COMMAND 20
#define MINUTES_IN_DAY 1440
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24


FILE *openfile(char filename[]) {
    // If file is able to be opened, return the opened file 

    FILE *files = fopen(filename, "r");
    if(files == NULL) {
        fprintf(stderr, "File does not exist or cannot be opened '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return files;
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
        if(strstr(days[i], day) != NULL){ // Compares whether given day is a valid day (or substring)
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
        if(strstr(months[i], month) != NULL){ // Compares whether given day is a valid day (or substring)
            num = i;
        }
    }
    return num;

}

void estimatecron(char *month, FILE *crontab_file, FILE *estimates_file){
    int maxCommand = 0;
    int invokedCommand = 0;
    char all[2] = "*"; //defining * to be all possible valid value

    struct Cron{
        char min[2];
        char hour[2];
        char day[2];
        char month[3];
        char date[3];
        char cmd[40];
    };

    struct Est{
        char command[40];
        char time[99999];
    };

    char line[MAX_LEN];


    // Reading estimates file line by line and putting contents into array of structures
    while(fgets(line, sizeof line, estimates_file) != NULL){
        char command[40];
        int minute = 0;

        int i = 0;
        if(line[0]=='#'){ //if line is comment line, continue to next line
            continue;
        }
        else if(line[i]==' '){//if the character is space, increment i
            i++;
        }     
    }
    printf("%s",line);
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




