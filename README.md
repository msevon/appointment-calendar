Appointment Calendar Program Readme


This is a C program designed to manage an appointment calendar. It allows users to add, delete, and view appointments within the calendar. The program provides a command-line interface for interacting with the calendar. Below, you'll find a comprehensive guide on how to use this program, its features, and its structure.


Compilation


Introduction<a name="introduction"></a>


This program was developed as a course project during the ELEC-A7100 spring 2021 course. It allows users to manage appointments through a set of commands, including adding, deleting, listing, saving, loading, and quitting. The maximum size of a description for an appointment is 20 characters.

Please note that the program does not support special characters (e.g., å, ä, ö) due to limitations in the C language's handling of character encodings.


Features<a name="features"></a>


Add Appointments: Users can add appointments by providing a description, month, day, and hour.

Delete Appointments: Appointments can be deleted by specifying the month, day, and hour.

List Appointments: Users can list all upcoming appointments.

Save and Load: The program allows users to save their calendar to a file and load it from a file.

Error Handling: The program checks for various errors, such as invalid inputs or overlong descriptions, and provides informative error messages.

Chronological Sorting: The calendar is automatically sorted chronologically based on months, days, and hours.


Code Structure<a name="code-structure"></a>


The code is structured as follows:

Main Function: The main function serves as the entry point of the program, where user commands are read and processed.

Calendar Structure: A structure Calendar is used to store appointments. It contains an array of Appointment structures. The maximum size of the calendar is 8760 appointments.

Command Processing: The readCommand function parses user commands and calls appropriate functions to perform actions like adding or deleting appointments.

File Handling: Functions readCalendar and writeCalendar handle reading and writing calendar data from/to files.

Appointment Handling: Functions addAppointment and deleteAppointment manage adding and deleting appointments while ensuring data validation and sorting.

Sorting: The sortChrono function is responsible for sorting the calendar in chronological order.

Printing Calendar: The printCalendar function displays upcoming appointments.


Compilation<a name="compilation"></a>


To compile and run the program, you can use a C compiler such as GCC. Here's a basic compilation command:

gcc -o calendar_program your_source_code.c

Replace your_source_code.c with the name of the source code file containing the provided code. After compilation, you can run the program as follows:

./calendar_program
