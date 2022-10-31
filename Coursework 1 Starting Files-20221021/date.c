#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "date.h"


typedef struct date {
	int day;
	int month;
	int year;
}Date;

Date* date_create(char* datestr) {
	Date* d = malloc(sizeof(Date));
	int len = strlen(datestr);
	if (len != 10)
	{
		return NULL;
	}
	int t_day = ( * (datestr)-'0') * 10 + ( * (datestr + 1)-'0');
	int t_month = ( * (datestr + 3)-'0') * 10 +( * (datestr + 4) - '0');
	int t_year = ( * (datestr + 6)-'0') * 1000 + ( * (datestr + 7)-'0') * 100 + ( * (datestr + 8)-'0') * 10 + ( * (datestr + 9)-'0');
	d->day = t_day;
	d->month = t_month;
	d->year = t_year;
	return d;
};

Date* date_duplicate(Date* d) {
	Date* new = malloc(sizeof(Date));
	if (!new)
	{
		return NULL;
	}
	new->day = d->day;
	new->month = d->month;
	new->year = d->year;
    return new;
};

int date_compare(Date* date1, Date* date2) {
	if (date1->year>date2->year)
	{
		return 1;
	}
	else if (date1->year < date2->year) {
		return -1;
	}
	else
	{
		if (date1->month>date2->month)
		{
			return 1;
		}
		else if (date1->month < date2->month) {
			return -1;
		}
		else
		{
			if (date1->day>date2->day)
			{
				return 1;
			}
			else if (date1->day < date2->day) {
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}
};
void date_destroy(Date* d) {
	free(d);
};


#endif /* _DATE_H_INCLUDED_ */