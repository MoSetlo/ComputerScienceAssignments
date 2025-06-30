#include "TileManager.h"


namespace stlmou001
{

    TileManager::TileManager() //Default constructor
    {

        tiles=nullptr;

    }

    //Method that populates the TileManager Class with input data

    void TileManager::UpdateDetails(int& paramfileRows, int& paramfileCols, int& paramgridSize, 
        std::vector<std::string> & paramfileHeader , char * paramfileChars , std::string&paramfileName, int& paramnumMoves) 
        {
            fileRows = paramfileRows;
            fileCols = paramfileCols;
            gridSize = paramgridSize;
            fileHeader = paramfileHeader;
            fileChars = convertTo2D(paramfileChars);
            //fileName = paramfileName;
            numMoves = paramnumMoves;

            int findStop = paramfileName.find(".");
            fileName = paramfileName.substr(0,findStop);


            resizePGM();

        }

//Converts the array stream of PGM characters into a 2D array representation of the orginal image
    unsigned char ** TileManager::convertTo2D(char * paramfileChar)
    {

        unsigned char **array2D;
        array2D = new unsigned char *[fileRows];
        int counter=0;

        for(int i=0 ; i<fileRows ; ++i)
        {
            array2D[i] = new unsigned char[fileCols];
            for (int j=0 ; j<fileCols ;++j)
            {
                array2D[i][j]=paramfileChar[counter++]; 

            }

            
        }


        return (unsigned char **)array2D;

    }    

//Resizes the PGM 2D array to be divisible by the user input grid size
    void TileManager::resizePGM()
    {

    fileRows = round(fileRows/gridSize)*gridSize;     
    fileCols = round(fileCols/gridSize)*gridSize;  
    std::ostringstream oss;
    oss<<fileCols<<" "<<fileRows;
    fileHeader[fileHeader.size()-2] = oss.str(); 

    //std::cout<<"The rows are " << fileRows <<" Columns are "<<fileCols<<" Product is " <<fileRows*fileCols<<std::endl;


    createTiles();

    }
//Creates tile objects and gives each tile a subset of the PGM 2D array  
    void TileManager::createTiles()
    {

        tiles = new Tile*[gridSize];
        int counter =0;
        int pointre=0;

        int unitTileRow= fileRows/gridSize;
        int unitTileCols = fileCols/gridSize;
        unsigned char ***temp2D; //Defines the grid area our charcters will populate

        temp2D = new unsigned char **[gridSize*gridSize];

        for (int gridRow=0 ; gridRow<gridSize ; gridRow++)
        {
            tiles[gridRow] = new Tile[gridSize];
            for (int gridCols=0 ; gridCols<gridSize ; gridCols++)
            {
                temp2D[pointre] = new unsigned char *[unitTileRow];
                //std::cout<<"Test 3D"<<std::endl;
                for (int charsRow=gridRow*unitTileRow; charsRow<(gridRow+1)*unitTileRow ; charsRow++)
                {
                    // if(counter<1)
                    // {
                        temp2D[pointre][charsRow % unitTileRow] = new unsigned char[unitTileCols];
                    // }
                    
                    for(int charsCol=gridCols*unitTileCols ; charsCol <(gridCols+1)*unitTileCols ; charsCol++)
                    {
                        temp2D[pointre][charsRow % unitTileRow][charsCol %unitTileCols] = fileChars[charsRow][charsCol];
                        //std::cout << gridRow<<" "<<gridCols<<" "<<charsRow<<" "<<charsCol<<" "<<charsRow % unitTileRow<<" "<<charsCol%unitTileCols<< std::endl;
                        

                    }
                    

                }

                tiles[gridRow][gridCols].setTileChar(temp2D[pointre]);
                tiles[gridRow][gridCols].setXPos(gridCols);
                tiles[gridRow][gridCols].setYPos(gridRow);

                counter=0;
                pointre++;

                
            }

        }


        std::cout<<"Test for creatTiles() completed"<<std::endl;
        blackenBox();


        

    }

    //Blacken the bottom write box
    void TileManager::blackenBox()
    {
        int unitTileRow= fileRows/gridSize;
        int unitTileCols = fileCols/gridSize;
        

        for(int row=0; row<unitTileRow;row++)
        {
            for (int col=0 ; col<unitTileCols ; col++)
            {
                tiles[gridSize-1][gridSize-1].getTileChar()[row][col] = 0;
            }
        }

        rowBlack = gridSize-1;
        colBlack = gridSize-1;

        std::cout<<"Test for blackenBox() completed"<<std::endl;

        moveTile();

        
        
    }


//Move tile and prints image state
void TileManager::moveTile(void)
    {
        //Print original image
        fromTileToTile();
        writeToFile(0);

    //Test a move from the last square to the second to last square\
    //Shoot should instatiate or copy constructor;
    std::vector<Tile> randHolder;
    //std::vector<unsigned char > randHolder;
     srand(time(0)); //random number gen


     for(int randy=0 ; randy<numMoves; randy++)
     {

    if(rowBlack < gridSize-1 )
    {
        randHolder.push_back(tiles[rowBlack +1][colBlack]);

    }
    
        if(rowBlack >0 )
    {
        randHolder.push_back(tiles[rowBlack-1][colBlack]);

    }
    

    //Check columns out of bounds
    if(colBlack < gridSize-1 )
    {
        randHolder.push_back(tiles[rowBlack][colBlack+1]);

    }
    
        if(colBlack >0 )
    {
        randHolder.push_back(tiles[rowBlack][colBlack-1]);


    }

    int randRow,randCol;

   int randNum = rand() % (randHolder.size());



    //Original location of random Tile
    //
    randRow = randHolder[randNum].getYPos();
    randCol = randHolder[randNum].getXPos();

    //std::cout<<randNum<<" " <<randRow<<randCol <<" "<<randHolder.size()<<" "<<rowBlack<<colBlack <<std::endl;



    tiles[randRow][randCol] = tiles[rowBlack][colBlack];
    tiles[rowBlack][colBlack] = randHolder[randNum];


    //Update Random tile to Black tile's old location

    tiles[rowBlack][colBlack].setYPos(rowBlack);
    tiles[rowBlack][colBlack].setXPos(colBlack);




    //Keep track of black tile

    rowBlack = randRow;
    colBlack = randCol;

    //reset vector

    //std::cout<<randNum<<" "<<randHolder.size()<<" "<<rowBlack<<colBlack <<std::endl;

    randHolder.clear();
    fromTileToTile();
    writeToFile(randy+1);

     }



    std::cout<<"Test for moveTile() completed"<<std::endl;





    }
    
    

    void TileManager::fromTileToTile(void)
    {

        int unitTileRow= fileRows/gridSize;
        int unitTileCols = fileCols/gridSize;
        unsigned char **temp2D;

        for (int gridRow=0 ; gridRow<gridSize ; gridRow++)
        {
            for (int gridCols=0 ; gridCols<gridSize ; gridCols++)
            {
                for (int charsRow=gridRow*unitTileRow; charsRow<(gridRow+1)*unitTileRow ; charsRow++)
                {
                    
                    for(int charsCol=gridCols*unitTileCols ; charsCol <(gridCols+1)*unitTileCols ; charsCol++)
                    {


                        fileChars[charsRow][charsCol] = tiles[gridRow][gridCols].getTileChar()[charsRow % unitTileRow][charsCol % unitTileCols];

                    }


                }

            }

        }

        //std::cout<<"Test for tiletoTile()  completed"<<std::endl;

    }
    
    
    
    void TileManager::writeToFile(int paramI)
    {

    std::string fileOut =fileName+ "-" + std::to_string(paramI) + ".pgm";    
 


    std::ofstream outf(fileOut, std::ios::binary | std::ios::app);

    for(int i=0 ; i<fileHeader.size() ; i++)
    {
        outf<<fileHeader.at(i) << std::endl;

    }

    std::ostringstream oss;

    for(int i=0 ; i<fileRows;i++)
    {

           for(int j=0;j<fileCols;j++)
           {
            oss << fileChars[i][j];
           }

    }


    outf<<oss.str() << std::endl;


    //std::cout<<"Finished"<<std::endl; 


    
    outf.close();


    }




}