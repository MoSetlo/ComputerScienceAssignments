CC=g++
CSTD=-std=c++20
LIBS=-lm

WCpp: driverWCpp.o WCpp.o
	$(CC) driverWCpp.o WCpp.o -o WCpp $(CSTD)

WCpp.o: WCpp.h WCpp.cpp
	$(CC) -c WCpp.cpp $(CSTD)

driverWCpp.o: driverWCpp.cpp
	$(CC) -c driverWCpp.cpp $(CSTD)

clean: 
	@rm -f *.o
	@rm WCpp
	
				 

