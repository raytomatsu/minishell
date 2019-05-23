#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readIn.h"
#include "user.h"

int main(int argc, char * args[]){

    initialize();
    readIn(args[1]); 
    char input[10];

    printf("Hello, please give an input. \n'x' would exit the program and simulator\n 's' will single step through one instruction \n 'p' will print the value of the program counter, X and Y and the current location \n 'c' will continue running until the specified adress is reached \n 'e' will exam print the value at the given location \n");

    while(1){
    scanf("%s", input);
    userInput(input);
    }
    
}       