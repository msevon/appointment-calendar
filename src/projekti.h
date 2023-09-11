/*Header file*/

/*define a single appointment structure*/

typedef struct Appointment{
  char desc[21];
  int month;
  int day;
  int hour;
  bool deleted;
} Appointment;

/*define calendar structure which stores all the appointments*/
typedef struct Calendar{
  struct Appointment *c;
  int numOfAppointments;
  int index;
} Calendar;

/*define functions*/
int writeCalendar(char* filename, Calendar* calendar);
struct Calendar readCommand(char *str, struct Calendar calendar);
struct Calendar sortChrono(struct Calendar calendar);
struct Calendar addAppointment(struct Calendar calendar, char *desc, int mm, int dd, int hh);
struct Calendar deleteAppointment(struct Calendar calendar, int mm, int dd, int hh);
void printCalendar(struct Calendar calendar);
