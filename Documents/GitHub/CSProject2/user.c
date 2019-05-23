#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readIn.h"
#include "user.h"

/****
 * This file is mainly the user input file in which the input from the user will be addressed.
 * */


//user inputs a string and does the specified actions needed.
void userInput(char *input){
    char* firstChar = substring(input,1,1);

    if(strcmp(firstChar,"x") == 0){
        exit(0);
    }
    if(strcmp(firstChar,"s") == 0){
        readOneStep();
    }
    if(strcmp(firstChar,"p") == 0){
        printValues();
    }
    if(strcmp(firstChar,"c") == 0){
        char *fakeAddress = substring(input,3,4);
        int address = (int)strtol(fakeAddress, NULL, 16);
        continueUntil(address);
    }
    if(strcmp(firstChar,"e") == 0){
        char *fakeAddress = substring(input,3,2);
        int address = (int)strtol(fakeAddress, NULL, 16);
        
    }
}

//function that substrings a string pointer.
char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
   
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position-1);      
      string++;  
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}