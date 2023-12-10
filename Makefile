CC = g++
CFLAGS = -g -Wall

all: lab

lab: main.cpp
	$(CC) $(CFLAGS) main.cpp dialog.h handle.h signal_processing.h dialog.cpp handle.cpp signal_processing.cpp -o ivanenko

clean:
	rm -f lab
