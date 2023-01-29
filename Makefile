EXE = server client
SOBJ = server.o connect.o lib.o books.o
COBJ = client.o connect.o
CC = gcc -Wall -g

all:	$(EXE)

server:	$(SOBJ)
	$(CC) -o server $(SOBJ)

client:	$(COBJ)
	$(CC) -o client $(COBJ)

server.o:	server.c defs.h
	$(CC) -c server.c

client.o:	client.c defs.h
	$(CC) -c client.c

connect.o:	connect.c defs.h
	$(CC) -c connect.c

lib.o:	lib.c defs.h
	$(CC) -c lib.c

books.o:	books.c defs.h
	$(CC) -c books.c

clean:
	rm -f $(EXE) $(SOBJ) $(COBJ)
