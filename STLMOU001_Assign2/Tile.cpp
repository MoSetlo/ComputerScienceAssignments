#include "Tile.h"

namespace stlmou001
{
    Tile::Tile()
    {
        xPos = 0;
        yPos = 0;
        gridType = "";
        tileChar = nullptr;
    }


    Tile::Tile(int x, int y , std::string type , unsigned char ** tile)
    {
        xPos = x;
        yPos = y;
        gridType = type;
        tileChar = tile;
    }

    unsigned char ** Tile::getTileChar()
    {
        return tileChar;
    }

    std::string Tile::getGridType()
    {
        return gridType;
    }

    int Tile::getXPos()
    {
        return xPos;
    }

    int Tile::getYPos()
    {
        return yPos;
    }

    void Tile::setTileChar(unsigned char** paramTile)
    {
        tileChar = paramTile;
    }

    void Tile::setGridType(std::string paramType)
    {
        gridType = paramType;
    }

    void Tile::setXPos(int paramX)
    {
        xPos=paramX;
    }

    void Tile::setYPos(int paramY)
    {
        yPos = paramY;
    }
}