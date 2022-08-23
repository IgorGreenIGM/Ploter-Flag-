### __MAKEFILE___ ###

CC = g++
CFLAGS = -m32
LDFLAGS = -m32 -L"./lib" -lopengl32 -lglut32
EXEC = bin/output.exe

all : $(EXEC)

$(EXEC): main.o argList.o treatment.o userInterface.o drawStream.o drawUtilities.o plot.o sorting.o streamRead.o streamOperations.o
		$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o:	src/main.cpp
		$(CC) -c $< $(CFLAGS)

argList.o: src/ArgManager/argList.cpp
		$(CC) -c $< $(CFLAGS)

treatment.o: src/ArgManager/treatment.cpp
		$(CC) -c $< $(CFLAGS)

userInterface.o: src/ArgManager/userInterface.cpp
		$(CC) -c $< $(CFLAGS)

drawStream.o: src/DrawingMethods/drawStream.cpp
		$(CC) -c $< $(CFLAGS)

drawUtilities.o: src/DrawingMethods/drawUtilities.cpp
		$(CC) -c $< $(CFLAGS)
	
plot.o: src/DrawingMethods/plot.cpp
		$(CC) -c $< $(CFLAGS)

sorting.o: src/DrawingMethods/sorting.cpp
		$(CC) -c $< $(CFLAGS)

streamRead.o: src/DrawingMethods/streamRead.cpp
		$(CC) -c $< $(CFLAGS)

streamOperations.o: src/streamOperations/streamOperations.cpp
		$(CC) -c $< $(CFLAGS)

clean:
		rm *.o

mrproper: clean 
		rm -f $(EXEC)