#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    char datestr[] = "05/11/2018";
    char *slash = "/";
    char* day = strtok(datestr , slash);
    char* month  = strtok(NULL , slash) ;
    char* year = strtok(NULL , slash);
    int int_day = strtol(day,NULL,10);
    int int_month = strtol(month,NULL,10);
    int int_year = strtol(year,NULL,10);
    printf ("%d\n",int_day);
    printf ("%d\n",int_month);
    printf ("%d\n",int_year);
}