CC=g++
CSTD=-std=c++20
LIBS=-lm

SlidyTile: driverSlidyTile.o TileManager.o Tile.o
	$(CC) driverSlidyTile.o TileManager.o Tile.o -o SlidyTile $(CSTD)

TileManager.o: TileManager.h TileManager.cpp
	$(CC) -c TileManager.cpp $(CSTD)


Tile.o: Tile.h Tile.cpp
	$(CC) -c Tile.cpp $(CSTD)	

driverSlidyTile.o: driverSlidyTile.cpp
	$(CC) -c driverSlidyTile.cpp $(CSTD)


clean: 
	@rm -f *.o
	@rm -f -- *-*.pgm
	@rm SlidyTile

imageClean:
	@rm -f -- *-*.pgm
	
				 

