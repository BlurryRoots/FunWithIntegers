SOURCE = src
BINARIES = bin

COMPILER = g++
CFLAGS = -g -Wall -std=c++11

ifeq ($(OS),Windows_NT)
	OUTFILE = main.exe
	CHMOD =
	RUN = $(BINARIES)/$(OUTFILE)
else
	OUTFILE = main
	CHMOD = chmod +x $(BINARIES)/$(OUTFILE)
	RUN = $(BINARIES)/./$(OUTFILE)
endif

clean:
	rm -fr $(BINARIES)
	mkdir $(BINARIES)

build:
	$(COMPILER) $(CFLAGS) -c $(SOURCE)/main.cpp -o $(BINARIES)/main.o
	$(COMPILER) $(CFLAGS) -c $(SOURCE)/SignedInteger.cpp -o $(BINARIES)/SignedInteger.o
	$(COMPILER) $(BINARIES)/SignedInteger.o $(BINARIES)/main.o -o $(BINARIES)/$(OUTFILE)
	$(CHMOD)

run:
	$(RUN)