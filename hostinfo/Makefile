CC = gcc
CFLAGS = -Wall -g
LDFLAGS = 
TARGET = hostinfo

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o $(LDFLAGS)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	rm -f $(TARGET) $(TARGET).o
