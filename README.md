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
