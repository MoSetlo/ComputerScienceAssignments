#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>

#ifndef TILE
#define TILE

namespace stlmou001
{


class Tile
{
    private:
    
        int xPos,yPos;
        unsigned char ** tileChar;
        std::string gridType;

    public:
    Tile();

    Tile(int x, int y , std::string type , unsigned char ** tile);


    unsigned char ** getTileChar();


    std::string getGridType();


    int getXPos();


    int getYPos();

    void setTileChar(unsigned char ** paramTile);


    void setGridType(std::string paramType);


    void setXPos(int paramX);


    void setYPos(int paramY);




};

}

#endif