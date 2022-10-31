#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "date.h"
#include <stdlib.h>

typedef struct date{
    int day;
    int month;
    int year;
    } Date;

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
    int length = strlen(datestr);
    if (length != 10){
    	return NULL;
    }
    char *slash = "/";
    char* day = strtok(datestr , slash);
    char* month  = strtok(NULL , slash) ;
    char* year = strtok(NULL , slash);
    int int_day = strtol(day,NULL,10);
    int int_month = strtol(month,NULL,10);
    int int_year = strtol(year,NULL,10);
    Date* datestructure = malloc(sizeof(Date));
    datestructure-> day = int_day;
    datestructure-> month = int_month;
    datestructure-> year = int_year;
    return datestructure;
};
    
/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){
    Date* new_datestructure = malloc(sizeof(Date));
    if (!new_datestructure){
    	return NULL;
    }
    new_datestructure-> day = d->day;
    new_datestructure-> month = d->month;
    new_datestructure-> year = d->year;
    return new_datestructure;
};


        
/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2){
    if (date1->year > date2->year || (date1->year == date2->year && date1->month > date2->month) || (date1->year == date2->year && date1->month == date2->month && date1->day > date2->day )){
        return 1;
    }
    else if (date1->year < date2->year || (date1->year == date2->year && date1->month < date2->month) || (date1->year == date2->year && date1->month == date2->month && date1->day < date2->day) ){
        return -1;
    }
    else{
        return 0;
    }
};
    

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
        free(d);
};

#endif /* _DATE_H_INCLUDED_ */
