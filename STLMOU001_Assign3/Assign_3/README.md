
# Image processing with connected components For C++

In this C++ project, we are given a greyscale input image (PGM) and asked to provide
an image processing class that can extract all the connected components for the image,
given some user-supplied threshold.


## C++ Classes

PGMimageProcessor: Responsible for loading PGM images, extracting connected components, filtering components by size, and writing components to a new PGM file.

ConnectedComponent: Represents a connected component in the image. It stores information about the component's ID, pixel count, and coordinates of pixels belonging to the component.

## Running Program

### Input

The program can be run by providing the user input directly into the console. In order to run the program, the user needs to specify atleast input image (must be a pgm image file).

To run the project on a Linux based system, run the following command in the terminal  (within the directory of the project folder )

```bash
  make
 ./pgmProcess [options] <inputfilename>

```

The user may run the program with all, some or no options. The options are specified below:

### Options

- `-s <min> <max>`: Set the minimum and maximum valid component sizes. Default is min = 3 and max = image width * image height.
- `-t <threshold>`: Set the threshold for component detection. Default is 128.
- `-p`: Print out all the component data along with the total component count and the sizes of the smallest and largest components.
- `-w <outPGMfile>`: Write out all retained components to a new PGM file specified by `<outPGMfile>`.

### Example

```bash
  make
 ./pgmProcess -s 5 1000 -t 130 -p -w outputimage.pgm <inputfilename>

```

## Acknowledgements
Marais, P. and Perkins, S. (2024) ‘C++’, 15 February. 
Breadth first search or BFS for a graph (2024) GeeksforGeeks. Available at: https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/, 20 March 2024. 



## Authors

- Moutloatsi Setlogelo





