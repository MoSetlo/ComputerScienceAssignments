CC=g++
CSTD=-std=c++20
LIBS=-lm

pgmProcess: driver.o PGMimageProcessor.o ConnectedComponent.o
	$(CC) driver.o PGMimageProcessor.o ConnectedComponent.o -o pgmProcess $(CSTD)

 ConnectedComponent.o: ConnectedComponent.h ConnectedComponent.cpp
	$(CC) -c ConnectedComponent.cpp $(CSTD)

PGMimageProcessor.o: PGMimageProcessor.h PGMimageProcessor.cpp 
	$(CC) -c PGMimageProcessor.cpp $(CSTD)	

driver.o: driver.cpp
	$(CC) -c driver.cpp $(CSTD)


clean: 
	@rm -f *.o
	@rm pgmProcess
	@rm -f -- *-*.pgm
	
				 

