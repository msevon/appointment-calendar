#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "projekti.h"

/*
APPOINTMENT CALENDAR PROGRAM
Miku Sevón 729501
ELEC-A7100 spring 2021 course project

Commands:
        Add an appointment: A 'description' 'mm' 'dd' 'hh'
        Delete an appointment: D 'mm' 'dd' 'hh'
        Print calendar: L
        Save calendar in file: W 'filename'
        Load calendar from file: O 'filename'
        Quit: Q
        
Maximum size of description is 20 characters. The program doesn't support
scandic characters (å,ä,ö) because the c-language specs don't automatically
handle anything other than 7 bit ASCII.

The maximum size of a calendar is 365 days *24 hours = 8760 appointments.
*/


/*main function of the program, asks commands until user quits or EOF*/
int main()
{   
    /*create calendar structure containing maximum of 8760 appointments*/
    struct Calendar calendar;
    calendar.c = malloc(sizeof(struct Appointment)*8760);
    calendar.numOfAppointments = 0;
    calendar.index = 0;
    char *str = malloc(50*sizeof(char));
    /*ask user input*/
    printf("Command: ");
    fgets(str, 50 ,stdin);
    while (!feof(stdin)) /*until EOF*/
    {   
        if (strcmp(str,"Q\n")==0) /*if user wants to quit*/
        {
            break;
        }
        else if (strcmp(str,"L\n")==0) /*print command*/
        {
            printCalendar(calendar);
        }
        else 
        {
            calendar = readCommand(str,calendar); /*add or delete appointment*/
        }
        printf("Command: "); /*asks for input again*/
        fgets(str, 50 ,stdin);
    }
    /*exits program and frees the calendar*/
    printf("Exiting program...");
    free(calendar.c);
    free(str);
}


/*reads a calendar from file and returns it, overwriting current calendar*/
struct Calendar readCalendar(char* filename, struct Calendar calendar)
{
    int lasqr = 0;
    int i = 0;

    /*strip filename and open it*/
    filename[strcspn(filename, "\n")] = 0;
    FILE *f = fopen(filename, "r");
    char *s = malloc(1000*sizeof(char));
    char *sog = s;

    if (!f) 
    {
        /*file not found*/
        free(s);
        printf("Couldn't find specified file.\n");
        return calendar;
        exit(EXIT_FAILURE);
    }
    while (fgets(s,1000,f) != NULL) 
    {
        lasqr++;
    }

    /*make an appointment array with maximum of 8760 appointments*/
    struct Appointment *appointments = malloc(sizeof(struct Appointment)*8760);

    s = sog;
    fclose(f);
    f = fopen(filename, "r");

    while (fgets(s,1000,f) != NULL) 
    {
        char desc[20];
        int month;
        int day;
        int hour;

        /*read data from file*/
        sscanf(s,"%s %d %d %d", desc, &month, &day, &hour);
        strcpy(appointments[i].desc, desc);
        appointments[i].month = month;
        appointments[i].day = day;
        appointments[i].hour = hour;
        appointments[i].deleted = false;

        i++;
    }

    /*store appointments in calendar*/
    free(calendar.c);
    calendar.c = appointments;
    calendar.index = i;
    calendar.numOfAppointments = i;
    free(s);
    fclose(f);
    
    /*return new loaded calendar*/
    printf("Calendar succesfully loaded!\n");
    return calendar;
}   

/*saves the calendar in a file*/
int writeCalendar(char* filename, Calendar* calendar)
{   
    /*check if calendar is empty*/
    if (calendar->numOfAppointments > 0)
    {
        filename[strcspn(filename, "\n")] = 0;

        FILE* OUT = fopen(filename, "w");
        int i;
        if (!OUT) {
            /*filename not valid*/
            printf("Please use valid filename.\n");
            return -1;
            exit(EXIT_FAILURE);
        }

        /*store all appointments*/
        for (i = 0; i<calendar->index; i++)
        {
            if (calendar->c[i].deleted == false) {
                char desc[21];
                char month[3];
                char day[3];
                char hour[3];
                /*format: 'desc mm dd hh'*/
                sprintf(desc,"%s", calendar->c[i].desc);
                sprintf(month,"%d", calendar->c[i].month);
                sprintf(day,"%d", calendar->c[i].day);
                sprintf(hour,"%d", calendar->c[i].hour);
                fputs(desc, OUT);
                fputs(" ", OUT);
                fputs(month, OUT);
                fputs(" ", OUT);
                fputs(day, OUT);
                fputs(" ", OUT);
                fputs(hour, OUT);
                fputs  ("\n", OUT);
            }
        }

        printf("Calendar succesfully saved!\n");
        fclose(OUT);
        return 0;
    }
    /*if calendar is empty*/
    printf("Can't save an empty calendar!\n");
    return -1;
}


/*reads user inputted command*/
struct Calendar readCommand(char *str, struct Calendar calendar)
{
    bool tooLong = false;
    int i = 0;
    char *token = strtok(str, " ");
    char *array[4];
    /*split command into array*/
    while (token != NULL)
    {
        if (i>4) 
        {
            if (token != NULL) 
            {
                tooLong = true;
            }
            break;
        }
        array[i]=token;
        i++;
        token = strtok(NULL, " ");
    }

    if (strcmp(array[0],"A") == 0 || strcmp(array[0],"A\n") == 0) /*user wants to add appointment*/
    {   
        if (i == 5 && tooLong == false ) 
        {
            char *desc = array[1];
            int mm = atoi(array[2]);
            int dd = atoi(array[3]);
            int hh = atoi(array[4]);
            calendar = addAppointment(calendar,desc,mm,dd,hh);
        }
        else
        {
            printf("Please use correct format: 'A description mm dd hh'\n");
        }
    }
    else if (strcmp(array[0],"D") == 0 || strcmp(array[0],"D\n") == 0) /*user wants to delete appointment*/
    {
        if (i == 4)
        { 
            int mm = atoi(array[1]);
            int dd = atoi(array[2]);
            int hh = atoi(array[3]);
            calendar = deleteAppointment(calendar,mm,dd,hh);
        }
        else
        {
            printf("Please use correct format: 'D mm dd hh'\n");
        }
    }
    else if (strcmp(array[0],"W") == 0) /*user wants to save the calendar*/
    {
        char *filename = array[1];
        writeCalendar(filename,&calendar);
    }
    else if (strcmp(array[0],"O") == 0) /*user wants to load a calendar*/
    {
        char *filename = array[1];
        calendar = readCalendar(filename, calendar);
    }
    else 
    { 
        /*users types invalid command*/
        printf("Invalid command!\n");
    }

    return calendar; /*return possibly modified calendar*/
}

/*sorts calendar chronological order*/
struct Calendar sortChrono(struct Calendar calendar) 
{
    for (int i = 0; i < calendar.index; i++) 
        {
            for (int j = i + 1; j < calendar.index; j++)
            {
                if (calendar.c[i].month > calendar.c[j].month) /*compares months first*/
                {
                    /*swap*/
                    struct Appointment a =  calendar.c[i];
                    calendar.c[i] = calendar.c[j];
                    calendar.c[j] = a;
                }
                else if (calendar.c[i].month == calendar.c[j].month) 
                {
                    if (calendar.c[i].day > calendar.c[j].day) /*if months match compare days*/
                    {
                        /*swap*/
                        struct Appointment a =  calendar.c[i];
                        calendar.c[i] = calendar.c[j];
                        calendar.c[j] = a;
                    }
                    else if (calendar.c[i].day == calendar.c[j].day) 
                    {
                        if (calendar.c[i].hour > calendar.c[j].hour) /*if days match compare hours*/
                        {
                            /*swap*/
                            struct Appointment a =  calendar.c[i];
                            calendar.c[i] = calendar.c[j];
                            calendar.c[j] = a;
                        }

                    }
                }
            }
        }
        /*return sorted calendar*/
        return calendar;
    }


/*adds a new appointment to the calendar*/
struct Calendar addAppointment(struct Calendar calendar, char *desc, int mm, int dd, int hh) 
{
    int descLen = strlen(desc);
    int errors = 0;
    if (descLen > 20) 
    {
        printf("Description is too long!\n");
        errors++;
    }
    if (hh < 0 || hh > 23) 
    {
        printf("Hours must be in the range (0,23)!\n");
        errors++;
    }
    if (dd < 1 || dd > 31) 
    {
        printf("Days must in the range (1,31)!\n");
        errors++;
    }
    if (mm < 1 || mm > 12) 
    {
        printf("Months must in the range (1,12)!\n");
        errors++;
    }
        if (errors == 0) {
        /*check if appointment already exists for current date*/
            for (int i=0; i<calendar.index; i++) 
            {
                if (calendar.c[i].month == mm && calendar.c[i].day == dd && calendar.c[i].hour == hh && calendar.c[i].deleted == false) 
                {
                    printf("You already have %s at %d.%d %d.00!\n",calendar.c[i].desc,  calendar.c[i].day, calendar.c[i].month, calendar.c[i].hour);
                    /*return non-modified calendar*/
                    return calendar;
                }
            }
            /*create an appointment and add input values*/
            struct Appointment a = {{'\0',0,0,0,false}};
            a.hour = hh;
            a.day = dd;
            a.month = mm;
            strcat(a.desc,desc);
            a.desc[descLen] = '\0';
    
            /*add appointment to the calendar*/
            calendar.c[calendar.index] = a;
            printf("Appointment for %s at %d.%d %d.00 successfully registered!\n",calendar.c[calendar.index].desc,  calendar.c[calendar.index].day, calendar.c[calendar.index].month, calendar.c[calendar.index].hour);
            calendar.numOfAppointments = calendar.numOfAppointments + 1;
            calendar.index = calendar.index + 1;
    }
    /*sort the calendar in chronological order*/
    calendar = sortChrono(calendar);
    /*return the updated calendar*/
    return calendar;
}

/*deletes an appointment from the calendar*/
struct Calendar deleteAppointment(struct Calendar calendar, int mm, int dd, int hh)
{
    /*compare all appointments in the calendar*/
    for (int i=0; i<calendar.index; i++) 
    {
        if (calendar.c[i].month == mm && calendar.c[i].day == dd && calendar.c[i].hour == hh && calendar.c[i].deleted == false) 
        {
            /*set 'deleted' flag on and decrease number of appointments*/
            calendar.c[i].deleted = true;
            calendar.numOfAppointments = calendar.numOfAppointments - 1;
            printf("Appointment for %s at %d.%d %d.00 succesfully deleted!\n",calendar.c[i].desc,  calendar.c[i].day, calendar.c[i].month, calendar.c[i].hour);
            /*return updated calendar*/
            return calendar;
        } 
    }
    /*didn't find the specified appointment. no changes made to the calendar*/
    printf("No appointments set for this date.\n");
    return calendar;
}

/*prints the calendar*/
void printCalendar(struct Calendar calendar) 
{
    int appointments = 0;
    for (int i = 0; i<calendar.index; i++) 
    {
        if (calendar.c[i].deleted == false) 
        {
            if (appointments == 0) 
            {
                printf("Your upcoming appointments:\n");
            }
            printf("%s at %d.%d %d.00\n",calendar.c[i].desc, calendar.c[i].day, calendar.c[i].month, calendar.c[i].hour);
            appointments++;
        }
    }
    if (appointments == 0) 
    {
        /*if calendar is empty*/
        printf("You don't have any upcoming appointments.\n");
    }
}
