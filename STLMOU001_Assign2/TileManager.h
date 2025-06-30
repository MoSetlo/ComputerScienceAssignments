#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>
#include "Tile.h"

#ifndef TILEMANAGER
#define TILEMANAGER

namespace stlmou001
{


class TileManager
{
    private:
        int fileRows,fileCols,gridSize,numMoves, rowBlack , colBlack;
        std::vector<std::string> fileHeader;
        std::string fileName;
        unsigned char **fileChars;
        Tile **tiles;
    public:
        TileManager();
        unsigned char ** convertTo2D(char * paramfileChar);
        void resizePGM(void);
        void UpdateDetails(int& paramfileRows, int& paramfileCols, int& paramgridSize, 
        std::vector<std::string> & paramfileHeader , char * paramfileChars, std::string &fileName, int &paramnumMoves);
        void createTiles(void);
        void blackenBox(void);
        void moveTile(void);
        void fromTileToTile(void);
        void writeToFile(int paramI); 

        

        


};

}

#endif

