FLAGS=-ansi -pedantic -Wall
PROGRAM=addressbook
SOURCES=addressbook.c addressbook_list.c addressbook_array.c commands.c helpers.c
HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)
TEXT=sml.txt med.txt lrg.txt
USER=PatrickDowlingPhoneBook

all: $(OBJECTS)
	gcc $(OBJECTS) -o $(PROGRAM)
addressbook.o: addressbook.c addressbook.h
	gcc $(FLAGS) -c addressbook.c
addressbook_list.o: addressbook_list.c addressbook_list.h
	gcc $(FLAGS) -c addressbook_list.c
addressbook_array.o: addressbook_array.c addressbook_array.h
	gcc $(FLAGS) -c addressbook_array.c
commands.o: commands.c commands.h 
	gcc $(FLAGS) -c commands.c
helpers.o: helpers.c helpers.h
	gcc $(FLAGS) -c helpers.c
clean:
	rm $(OBJECTS) $(PROGRAM)
debug:
	gcc $(FLAGS) -g $(SOURCES) -o $(PROGRAM)
archive:
	zip $(USER).zip $(SOURCES) $(HEADERS) $(TEXT) Makefile
