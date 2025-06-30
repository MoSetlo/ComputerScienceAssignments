
# Unix Emulation Command: "wc" for C++


This C++ project emulates the Unix command "wc" allowing the user to provide text input ,either through file output redirection or console input. The user will then receive the line count, word count and character count from the input text. Extra functionality has been provided to count the frequency of characters and display these characters along with their respective frequency.


## Java Classes

Included in this project are two cpp files and one header file. Their name and function can be described as follows: 

- WCpp.h: header file for declaring methods to count the lines , words and characters of console input , as well as a declared method to count the frequency of characters and display these characters along with their respective frequency.
- WCpp.h: header file for defining methods to count the lines , words and characters of console input, as well as a defined method to count the frequency of characters and display these characters along with their respective frequency.
- driverWCpp: driver file containing the main method. Contains functionality to accept console input and call the methods from WCpp.h and WCpp.cpp

## Running Program

### Input

The program can be run with the help of a textfile in the directory consisting of user input or by providing the user input directly into the console.

An example of user input may include:
The rain in Spain
falls mainly on the plain


To run the project on a Linux based system, run the following command in the terminal  (within the directory of the project folder )

```bash
  make
  cat "yourfile.txt" | ./WCpp


```
To run the project on a Linux based system and if the user would like to use console input instead of a textfile, run the following command in the terminal:

```bash
  make
  ./WCpp


```

*Note in order to terminate console input, press CTRL+D*
### Output

After providing a series of inputs strings, the program outputs:
- The line count , word count and character count as well as present characters along with their respective frequency.

if we use the example input of:
The rain in Spain
falls mainly on the plain

The output will be in the form:
2 9 35 [a:5 e:2 f:1 h:2 i:5 l:4 m:1 n:6 o:1 p:2 r:1 s:2 t:2 y:1 ]

## Acknowledgements
Marais, P. and Perkins, S. (2024) ‘C++’, 15 February. 




## Authors

- Moutloatsi Setlogelo





