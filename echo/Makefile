CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lpthread

all: echoclient echoserver

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

echoclient.o: echoclient.c csapp.h
	$(CC) $(CFLAGS) -c echoclient.c

echoserver.o: echoserver.c csapp.h
	$(CC) $(CFLAGS) -c echoserver.c

echoclient: echoclient.o csapp.o
	$(CC) $(CFLAGS) echoclient.o csapp.o -o echoclient $(LDFLAGS)

echoserver: echoserver.o csapp.o
	$(CC) $(CFLAGS) echoserver.o csapp.o -o echoserver $(LDFLAGS)

# Creates a tarball in ../echoclientlab-handin.tar that you can then
# hand in. DO NOT MODIFY THIS!

handin:
	(make clean; cd ..; tar cvf $(USER)-echoclientlab-handin.tar echoclientlab-handout --exclude tiny --exclude nop-server.py --exclude echoclient --exclude driver.sh --exclude port-for-user.pl --exclude free-port.sh --exclude ".*")

clean:
	rm -f *~ *.o echoclient echoserver core *.tar *.zip *.gzip *.bzip *.gz