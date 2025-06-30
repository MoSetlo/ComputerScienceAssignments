
# Image-based Slide Puzzle Game for C++

In this C++ project, we turn a given image into the beginnings of a slide puzzle game. These are 2D tile-based board games where the user is given an image represented as a grid of randomized tiles, in which the goal is to slide tiles left, right, up and down in the hopes of rebuilding the original image.
 
In this C++ project, instead of randomizing the image tiles and allwoing a user to solve the image, we’re interested in generating candidate play states (represented as an
sequence of images) for others to solve. The user here may input the image, the preferred grid size of game, and the number of possible play states to generate. 


## C++ Classes

Included in this project are three cpp files and two header file. Their name and function can be described as follows: 

- TileManager.h: header file for declaring methods to represent the image in grid form, to create and manage individual tiles ,to create candidate play states, and to output these candidate play states as images.
- TileManager.cpp: CPP file for defining methods to represent the image in grid form, to create and manage individual tiles ,to create candidate play states, and to output these candidate play states as images.
- Tile.h: header file for declaring methods to hold and return the subset of the main image
- Tile.cpp: CPP file for defining methods to hold and return the subset of the main image
- driverSlidyTile.cpp: driver file containing the main method. Contains functionality to accept console input, open the image file and read its contents, passing these arguments and contents to TileManager.

## Running Program

### Input

The program can be run by providing the user input directly into the console. In order to run the program, the user needs to specify the input image (must be a pgm image file), the grid size(must be odd) and the number of play states: 


To run the project on a Linux based system, run the following command in the terminal  (within the directory of the project folder )

```bash
  make
 ./driverSlidyTile -s <"your grid size"> -i <"your pgm image"> -n <"your number of playstates">


```

### Output

After providing the required console arguments, the user will receive a series of pgm image play states in the order of play, from 0 to the number of play states specified. 
For example, if a user inputs an an image called "myimage.pgm" specifying 3 play state, the output images will be ordered "myimage-0.pgm" , "myimage-1.pgm" , "myimage-2.pgm" and "myimage-3.pgm". The 0 pgm state is the original image state before sliding.


### Makefile
Makefile contains additional clean call called imageClean to only delete output images.
run as follows: "make imageClean"


## Acknowledgements
Marais, P. and Perkins, S. (2024) ‘C++’, 15 February. 




## Authors

- Moutloatsi Setlogelo





