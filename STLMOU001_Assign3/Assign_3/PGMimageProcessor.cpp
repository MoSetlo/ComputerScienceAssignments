#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

namespace stlmou001{

// Constructor
PGMimageProcessor::PGMimageProcessor(const std::string& inputFile) 
{
    //set values to default
    fileName=inputFile;
    threadshold =128;
    min = 3;
    max = -1;
    printData = false;
    outputImage="";
}

// Destructor
PGMimageProcessor::~PGMimageProcessor() {

    //deletion of 2D char arrays fileChars & visited
    for (int i = 0; i < fileRows; ++i) {
        delete[] fileChars[i];
        delete[] visited[i];
    }
    delete[] fileChars;
    delete[] visited;
    
}

// Copy constructor
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other) {


    

    components = other.components;
    fileRows = other.fileRows;
    fileCols = other.fileCols;
    fileHeader = other.fileHeader;
    fileName = other.fileName;
    fileChars = other.fileChars;
    visited = other.visited;
    threadshold = other.threadshold;
    min = other.min;
    max = other.max;
    printData = other.printData;
    outputImage = other.outputImage;

    if (fileCols>0 and fileRows>0)
    {
        
        fileChars = new unsigned char *[fileRows];
        visited = new bool *[fileRows];

        for(int i=0 ; i<fileRows ; ++i)
        {
            fileChars[i] = new unsigned char[fileCols];
            visited[i] = new bool[fileCols];
            for (int j=0 ; j<fileCols ;++j)
            {
                fileChars[i][j]=other.fileChars[i][j]; 
                visited[i][j] = other.visited[i][j];;

            }

            
        }

    }

    

    
}

// Move constructor
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other) :
    components(std::move(other.components)),
    fileRows(other.fileRows),
    fileCols(other.fileCols),
    fileHeader(std::move(other.fileHeader)),
    fileName(std::move(other.fileName)),
    fileChars(other.fileChars),
    visited(other.visited),
    threadshold(other.threadshold),
    min(other.min),
    max(other.max),
    printData(other.printData),
    outputImage(std::move(other.outputImage))

 {
    // Delete the dynamically allocated memory for fileChars and visited;
        for (int i = 0; i < fileRows; ++i) {
            delete[] other.fileChars[i];
            delete[] other.visited[i];
        }
        delete[] other.fileChars;
        delete[] other.visited;

        // Reset the pointers
        other.fileChars = nullptr;
        other.visited = nullptr;
    
}

// Copy assignment operator
PGMimageProcessor& PGMimageProcessor::operator=(const PGMimageProcessor& other) {

    if(this!=&other)
    {

    

    components = other.components;
    fileRows = other.fileRows;
    fileCols = other.fileCols;
    fileHeader = other.fileHeader;
    fileName = other.fileName;
    fileChars = other.fileChars;
    visited = other.visited;
    threadshold = other.threadshold;
    min = other.min;
    max = other.max;
    printData = other.printData;
    outputImage = other.outputImage;


        
        fileChars = new unsigned char *[fileRows];
        visited = new bool *[fileRows];

        for(int i=0 ; i<fileRows ; ++i)
        {
            fileChars[i] = new unsigned char[fileCols];
            visited[i] = new bool[fileCols];
            for (int j=0 ; j<fileCols ;++j)
            {
                fileChars[i][j]=other.fileChars[i][j]; 
                visited[i][j] = other.visited[i][j];;

            }

            
        }

    }

    return *this;
    }

    


// Move assignment operator
PGMimageProcessor& PGMimageProcessor::operator=(PGMimageProcessor&& other) 
    {
    if(this!=&other)
    {

    components = (std::move(other.components));
    fileRows = (other.fileRows);
    fileCols = (other.fileCols),
    fileHeader = (std::move(other.fileHeader));
    fileName = (std::move(other.fileName));
    fileChars = (other.fileChars);
    visited = (other.visited);
    threadshold = (other.threadshold);
    min = (other.min);
    max = (other.max);
    printData = (other.printData);
    outputImage = (std::move(other.outputImage));


        
        // Delete the dynamically allocated memory for fileChars and visited
        for (int i = 0; i < fileRows; ++i) {
            delete[] other.fileChars[i];
            delete[] other.visited[i];
        }
        delete[] other.fileChars;
        delete[] other.visited;

        // Reset the pointers
        other.fileChars = nullptr;
        other.visited = nullptr;

    }

    return *this;
}

// Method to extract connected components
int PGMimageProcessor::extractComponents(const int & threshold, const int& minValidSize) 
{

    //parameters for neighboring equivalent test
    int dx[] = {0 ,1,0,-1};
    int dy[] = {-1,0,1,0};
    int componentCount = 0;

    for(int row=0 ; row<fileRows ; row++)
    {
        for(int col=0 ; col<fileCols ; col++)
        {
            //We check whether we are above the threshold
            if(!visited[row][col] && fileChars[row][col] >= threadshold)
            {
                visited[row][col] = true;
                
                std::shared_ptr<ConnectedComponent> component(new ConnectedComponent(componentCount++));
                //std::cout<<"Component ID: " << components.size() <<" created"<<std::endl;
                std::queue<std::pair<int,int>> queQ;
                queQ.push(std::make_pair(col,row));
                //idCount++;

                //BFS method

                while(!queQ.empty())
                {
                    int x = queQ.front().first;
                    int y = queQ.front().second;
                    queQ.pop();

                //Check if there is already an existing component we can merrge with
                    for (const std::shared_ptr<ConnectedComponent>& existingComponent : components) {
                        if (existingComponent->containsPixel(x, y)) {
                            // Merge current component with existing component
                            component->mergeWith(*existingComponent);
                            break; // Exit loop after merging
                        }
                    }


                    component -> addPixel(x,y); 

                    //Check for surrounding pixels
                    for(int k=0 ; k<4 ; ++k)
                    {
                        int nx = x+ dx[k];
                        int ny = y + dy[k];

                        //neighbour condition to see if pixel is within bounds of image
                        if(nx>=0 && nx<fileCols && ny >= 0 && ny < fileRows && !visited[ny][nx] && fileChars[ny][nx] >= threshold)
                        {
                            queQ.push(std::make_pair(nx,ny));
                            visited[ny][nx] = true;
                        }
                    }
                }


                if(component->getNumPixels() >= minValidSize)
                {
                    components.push_back(component);
                }
                

                //idCount++;
            }

        }
    }

    //writeComponents("Sam");



    filterComponentsBySize(minValidSize , max);

    return components.size();
}

// Method to filter components by size
int PGMimageProcessor::filterComponentsBySize(const int & minSize, const int & maxSize) 
{
    //std::cout<<"Filter Started: "<<components.size()<<" "<<maxSize <<std::endl; 
    //==========sort the vector by low to pop off high values===========
    sortComponentsLow();
    int posH = 0;
    bool flag = false;


    //=======Iterator Version======
    for(std::vector<std::shared_ptr<ConnectedComponent>>::const_iterator it=components.begin() ; it!=components.end() ; ++it)
    {

        if((*it)->getNumPixels()> maxSize)
        {
            flag = true;
            //std::cout<<"Found Max Size " << components[posH]->getNumPixels()<<" at " <<posH<<std::endl; 
            break;
        }
        //std::cout<<"Check Max Size " << components[posH]->getNumPixels()<<std::endl; 
        posH++;

    }
    //std::cout<<posH<<std::endl;
    //posH--;


    //std::cout<<"Before Started: "<<components.size()<<" "<<components.size() - posH <<std::endl; 
    if(flag && components.size()-(components.size()-(posH+1))>1){
    components.erase(components.begin()+posH, components.end());
    }
    else if(flag && components.size()-(components.size()-(posH+1))==1)
    {
        std::cout<<"Maximum components could not be filtered: Result would be NULL Component Vector"<<std::endl;
    }


   //std::cout<<"After Started: "<<components.size()<<" "<<components.size() - posH <<std::endl; 

    //Erase low components -2nd Scan
    //========sort vector from high to low========
    sortComponentsHigh();
    posH = 0;
    flag = false;



    //========Iterator Version==========
    for(std::vector<std::shared_ptr<ConnectedComponent>>::const_iterator it=components.begin() ; it!=components.end() ; ++it)
    {

        if((*it)->getNumPixels()< minSize)
        {
            flag = true;
            //std::cout<<"Found Max Size " << components[posH]->getNumPixels()<<" at " <<posH<<std::endl; 
            break;
        }
        //std::cout<<"Check Max Size " << components[posH]->getNumPixels()<<std::endl; 
        posH++;

    }

    //posH--;

    if(flag && components.size()-(components.size()-(posH+1))>1){
    components.erase(components.begin()+posH, components.end());
    }
    else if(flag && components.size()-(components.size()-(posH+1))==1)
    {
        std::cout<<"Minimum components could not be filtered: Result would be NULL Component Vector"<<std::endl;
    }

    //===========Readjust the componentsID================

    for (int m=0 ; m<components.size() ; m++)
    {
        components[m] -> setID(m+1);
    }

    //writeComponents(fileName);
    return components.size();
}

// =======Method to write components to a PGM file========
bool PGMimageProcessor::writeComponents(const std::string& outFileName) 
{

    convertToBlack(threadshold);

    //std::cout<<"Number of components: " << components.size() << std::endl;

for(int k=0 ; k < components.size() ; ++k)
{
    std::vector<std::pair<int, int>> pixels = components.at(k) ->getPixels();   
    for(int l =0 ; l<pixels.size() ; l++)
    {
        int x = pixels.at(l).first;
        int y = pixels.at(l).second;

        fileChars[y][x] = 255;
    }
}

    //printFullData();

    writeToFile(outFileName);

    return true;
}

// Getter methods
int PGMimageProcessor::getComponentCount() const {


    return components.size();
}

//header description
void PGMimageProcessor::sortComponentsLow(void)
{

        std::sort(components.begin(), components.end(), [](const std::shared_ptr<ConnectedComponent>& a, const std::shared_ptr<ConnectedComponent>& b) {
        return a->getNumPixels() < b->getNumPixels(); // Sort from low to high
    });
}


//header description
void PGMimageProcessor::sortComponentsHigh(void)
{

    std::sort(components.begin(), components.end(), [](const std::shared_ptr<ConnectedComponent>& a, const std::shared_ptr<ConnectedComponent>& b) {
        return a->getNumPixels() > b->getNumPixels(); // Sort from high to low
    });

}

// Getter methods
int PGMimageProcessor::getLargestSize() const 
{

    return components.at(0) ->getNumPixels();
}

int PGMimageProcessor::getSmallestSize() const {

    return components.at(components.size()-1) ->getNumPixels();
}

// Method to print component data
void PGMimageProcessor::printComponentData(const ConnectedComponent& theComponent) const 
{


        std::cout<<"Component ID:" << theComponent.getId() << " contains " <<theComponent.getNumPixels() <<" pixels" <<std::endl;
        
    
    
}

//Header description
void PGMimageProcessor::printFullData(void)
{

    for(std::vector<std::shared_ptr<ConnectedComponent>>:: const_iterator i=components.begin() ; i!=components.end(); i++)
    {
        printComponentData(**i);
    }

    std::cout<<"Total Number of Components: "<<getComponentCount() << std::endl;
    std::cout<<"Size of Largest Component: "<<getLargestSize()<<" pixels"<<std::endl;
    std::cout<<"Size of Smallest Component: "<<getSmallestSize()<<" pixels"<<std::endl;





}

//Header description
int PGMimageProcessor::readPGM(const int & argcParam , char * argvParam[])
{

    std::string strLine;


    //Test for minimum number of command line arguments
    if(argcParam<2)
    {
        std::cout<<"Not enough arguments were given"<<std::endl;

        return 0;
    }
    else
    {
        fileName = argvParam[argcParam-1];

        std::vector<std::string> args(argvParam, argvParam + argcParam);

        for (size_t i = 1; i < args.size(); ++i) 
        {
        if (args[i] == "-s" && i + 2 < args.size()) {
            min = std::stoi(args[i + 1]);
            std::cout<<"Min updated:" << min<< std::endl;
            max = std::stoi(args[i + 2]);
            i += 2;
            std::cout<<"Max updated:" <<max<< std::endl;
        } 
        else if (args[i] == "-t" && i + 1 < args.size()) {
            threadshold = std::stoi(args[i + 1]);
            std::cout<<"Threadshold updated:" << threadshold<< std::endl;
            ++i;
        } else if (args[i] == "-p") {
            printData = true;
        } else if (args[i] == "-w" && i + 1 < args.size()) {
            outputImage = args[i + 1];
            ++i;
        } 
        }
    



    //Input file existence check
   std::ifstream in(fileName, std::ios::binary);
    if(!in)
    {
        std::cerr << "Couldn't open file " << fileName << std::endl; 
    }

    //File reading until we hit the character '255', we switch to char byte read there after
    bool flag = false;
    while(!in.eof() && !flag)
    {
        getline(in,strLine);

     fileHeader.push_back(strLine);

     if(strLine == "255")  
     {
        flag = true;
        //cout<<"We detected that sonova bish"<<endl;
     }

    }
    
    std:: istringstream iss(fileHeader.at(fileHeader.size()-2));

    iss>>fileCols>>fileRows;

    char array[fileCols*fileRows];

    if(max<0)
    {
        max = fileCols*fileRows;
    }
    

    //char byte read into array;
    while(!in.eof())
    {
        in.read(array,fileCols*fileRows);
    }

    convertTo2D(array);

    in.close();


    

    return 1; // Check for correct file reading


}

}

// Header Description
    bool PGMimageProcessor::printStatus(void)
    {
        return printData;
    }

    std::string PGMimageProcessor::outputStatus(void)
    {
        

        return outputImage;
    }


//Method to create 2D array of PGM characters
void PGMimageProcessor::convertTo2D(const char * paramfileChar)
    {

        fileChars = new unsigned char *[fileRows];
        visited = new bool *[fileRows];
        
        int counter=0;

        for(int i=0 ; i<fileRows ; ++i)
        {
            fileChars[i] = new unsigned char[fileCols];
            visited[i] = new bool[fileCols];
            for (int j=0 ; j<fileCols ;++j)
            {
                fileChars[i][j]=paramfileChar[counter++]; 
                visited[i][j] = false;

            }

            
        }

        //convertToBlack();

        extractComponents(threadshold,min);

        //return (unsigned char **)array2D;

    }    

//Header description
void PGMimageProcessor::convertToBlack(const int & thresh)
{
        int counter =0;
        for(int i=0 ; i<fileRows ; ++i)
        {

            for (int j=0 ; j<fileCols ;++j)
            {
                // if(fileChars[i][j]>=thresh)
                // {
                //     fileChars[i][j]=255;


                // }
                // else
                // {
                    fileChars[i][j]=0;
                // }

            }

            
        }

    


}


//Header description
void PGMimageProcessor::writeToFile(const std::string& outFileName)
    {



    //std::string fileOut =fileName+ "-Out"+ ".pgm";    
 

    //=========Open file in binary and print characters============
    std::ofstream outf(outFileName, std::ios::binary | std::ios::app);

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