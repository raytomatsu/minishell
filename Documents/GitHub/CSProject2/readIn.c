#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readIn.h"

/**
 * This file takes in the char byte array and then points to the 
 * correct function in which it will do the suggested function the
 * opCode allows the function to do.
 * */


void (*opCode[256])();

unsigned char status = 0;
unsigned char A, X, Y;
unsigned char result [70000];
unsigned int pC = 256;
unsigned int sP = 0xFFF0;

//inialize all the opcodes to their respective functions
void initialize(){

opCode[0x69] = ADC_immediate;
opCode[0x65] = ADC_zeroPage;
opCode[0x75] = ADC_zeroPageX;
opCode[0x6D] = ADC_absolute;
opCode[0x7D] = ADC_absoluteX;
opCode[0x79] = ADC_absoluteY;
opCode[0x61] = ADC_indirectX;
opCode[0x71] = ADC_indirectY;

opCode[0x29] = AND_immediate;
opCode[0x25] = AND_zeroPage;
opCode[0x35] = AND_zeroPageX;
opCode[0x2D] = AND_absolute;
opCode[0x3D] = AND_absoluteX;
opCode[0x39] = AND_absoluteY;
opCode[0x21] = AND_indirectX;
opCode[0x31] = AND_indirectY;

opCode[0x0A] = ASL_accumulator;
opCode[0x06] = ASL_zeroPage;
opCode[0x16] = ASL_zeroPageX;
opCode[0x0E] = ASL_absolute;
opCode[0x1E] = ASL_absoluteX;

opCode[0x24] = BIT_zeroPage;
opCode[0x2C] = BIT_absolute;

opCode[0x30] = BMI_relative;
opCode[0xD0] = BNE_relative;
opCode[0x10] = BPL_relative;
opCode[0x90] = BCC;
opCode[0xB0] = BCS;
opCode[0xF0] = BEQ;
opCode[0x00] = BRK;
opCode[0x50] = BVC;
opCode[0x70] = BVS;

opCode[0x18] = CLC;
opCode[0xD8] = CLD;
opCode[0x58] = CLI;
opCode[0xB8] = CLV;

opCode[0xC9] = CMP_immediate;
opCode[0xC5] = CMP_zeroPage;
opCode[0xD5] = CMP_zeroPageX;
opCode[0xCD] = CMP_absolute;
opCode[0xDD] = CMP_absoluteX;
opCode[0xD9] = CMP_absoluteY;
opCode[0xC1] = CMP_indirectX;
opCode[0xD1] = CMP_indirectY;

opCode[0xE0] = CPX_immediate;
opCode[0xE4] = CPX_zeroPage;
opCode[0xEC] = CPX_absolute;

opCode[0xC0] = CPY_immediate;
opCode[0xC4] = CPY_zeroPage;
opCode[0xCC] = CPY_absolute;

opCode[0xC6] = DEC_zeroPage;
opCode[0xD6] = DEC_zeroPageX;
opCode[0xCE] = DEC_absolute;
opCode[0xDE] = DEC_absoluteX;

opCode[0xCA] = DEX_implied;
opCode[0x88] = DEY_implied;

opCode[0x49] = EOR_immediate;
opCode[0x45] = EOR_zeroPage;
opCode[0x55] = EOR_zeroPageX;
opCode[0x4D] = EOR_absolute;
opCode[0x5D] = EOR_absoluteX;
opCode[0x59] = EOR_absoluteY;
opCode[0x41] = EOR_indirectX;
opCode[0x51] = EOR_indirectY;

opCode[0xE6] = INC_zeroPage;
opCode[0xF6] = INC_zeroPageX;
opCode[0xEE] = INC_absolute;
opCode[0xFE] = INC_absoluteX;

opCode[0xE8] = INX_implied;
opCode[0xC8] = INY_implied;

opCode[0x4C] = JMP_absolute;
opCode[0x6C] = JMP_indirect;

opCode[0x20] = JSR;

opCode[0xA9] = LDA_immediate;
opCode[0xA5] = LDA_zeroPage;
opCode[0xB5] = LDA_zeroPageX;
opCode[0xAD] = LDA_absolute;
opCode[0xBD] = LDA_absoluteX;
opCode[0xB9] = LDA_absoluteY;
opCode[0xA1] = LDA_indirectX;
opCode[0xB1] = LDA_indirectY;

opCode[0xA2] = LDX_immediate;
opCode[0xA6] = LDX_zeroPage;
opCode[0xB6] = LDX_zeroPageY;
opCode[0xAE] = LDX_absolute;
opCode[0xBE] = LDX_absoluteY;

opCode[0xA0] = LDY_immediate;
opCode[0xA4] = LDY_zeroPage;
opCode[0xB4] = LDY_zeroPageX;
opCode[0xAC] = LDY_absolute;
opCode[0xBC] = LDY_absoluteX;

opCode[0x4A] = LSR_accumulator;
opCode[0x46] = LSR_zeroPage;
opCode[0x56] = LSR_zeroPageX;
opCode[0x4E] = LSR_absolute;
opCode[0x5E] = LSR_absoluteX;

opCode[0xEA] = NOP;

opCode[0x09] = ORA_immediate;
opCode[0x05] = ORA_zeroPage;
opCode[0x15] = ORA_zeroPageX;
opCode[0x0D] = ORA_absolute;
opCode[0x1D] = ORA_absoluteX;
opCode[0x19] = ORA_absoluteY;
opCode[0x01] = ORA_indirectX;
opCode[0x11] = ORA_indirectY;

opCode[0x48] = PHA;
opCode[0x08] = PHP;
opCode[0x68] = PLA;
opCode[0x28] = PLP;

opCode[0x2A] = ROL_accumulator;
opCode[0x26] = ROL_zeroPage;
opCode[0x36] = ROL_zeroPageX;
opCode[0x2E] = ROL_absolute;
opCode[0x3E] = ROL_absoluteX;

opCode[0x6A] = ROR_accumulator;
opCode[0x66] = ROR_zeroPage;
opCode[0x76] = ROR_zeroPageX;
opCode[0x6E] = ROR_absolute;
opCode[0x7E] = ROR_absoluteX;

opCode[0x40] = RTI;
opCode[0x60] = RTS;

opCode[0xE9] = SBC_immediate;
opCode[0xE5] = SBC_zeroPage;
opCode[0xF5] = SBC_zeroPageX;
opCode[0xED] = SBC_absolute;
opCode[0xFD] = SBC_absoluteX;
opCode[0xF9] = SBC_absoluteY;
opCode[0xE1] = SBC_indirectX;
opCode[0xF1] = SBC_indirectY;

opCode[0x38] = SEC;
opCode[0xF8] = SED;
opCode[0x78] = SEI;

opCode[0x85] = STA_zeroPage;
opCode[0x95] = STA_zeroPageX;
opCode[0x8D] = STA_absolute;
opCode[0x9D] = STA_absoluteX;
opCode[0x99] = STA_absoluteY;
opCode[0x81] = STA_indirectX;
opCode[0x91] = STA_indirectY;

opCode[0x86] = STX_zeroPage;
opCode[0x96] = STX_zeroPageY;
opCode[0x8E] = STX_absolute;

opCode[0x84] = STY_zeroPage;
opCode[0x94] = STY_zeroPageX;
opCode[0x8C] = STY_absolute;

opCode[0xAA] = TAX;
opCode[0xA8] = TAY;
opCode[0xBA] = TSX;
opCode[0x8A] = TXA;
opCode[0x9A] = TXS;
opCode[0x98] = TYA;
}

//this function reads the input file and creates a byte array based on it 
void readIn(char * file)
{
   FILE * pFile;
   char mystring [100];

   pFile = fopen (file, "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     while(fgets (mystring , 100 , pFile) != NULL){
       puts (mystring);
       if(strstr(mystring,"ENDHEAD")){
         break;
       }
   } 
   if(pFile!=NULL){
   fread(result+256,sizeof(char),20000,pFile);
   fclose(pFile);
   }
   for(int i = 256; i<290; i++){
     printf("HEX 0x%x", result[i]);
   }
 }
}

//reads one step of the byte Array 
void readOneStep(){
  readOpCode(result[pC]);
}

//thie function will continue the program continue until it reaches the point of the argument
void continueUntil(int address){
  while(pC != address){
    readOneStep();
  }
}
//this examines the content of the byte array in the specified index 
void printZero(char byte){
  printf("Examine 0x%x", result[byte]);
}

/*
*prints the value of the program at the current status
*/
void printValues(){
  printf("0x%x the value of the program Counter\n",result[pC]);
  printf("0x%x the value of the A accumulator \n",A);
  printf("0x%x the value of the X register\n", X);
  printf("0x%x the value of the Y register\n", Y);
  printf("0x%x the current location\n",pC);
}


/****
 * Reset and set the Adressed as needed
 * if A ==0 will set the zero flag off vice versa
 * The same for negative
 * */
void flagADC(){
  if(A == 0){
        zeroOn();
      }else{
        zeroOff();
      }
      if(A>>7 == 0){
        negativeOn();
      }else{
        negativeOff();
      }
}

//Turns the negative status on 
void negativeOn(){
status = status | 0x80;
}

//turns the negative status off
void negativeOff(){
  status = status & 0x7F;
  return;
}

//returns the negative status 
int checkNegative(){
  return status >> 7;
}

//turns the zero flag on 
void zeroOn(){
  status = status | 0x02;
}

//turns the zero flag off
void zeroOff(){
  status = status & 0xFD;
}

//returns the zero status
int checkZero(){
  int check = (status & 0x02) >> 1;
  return check;
}

//turns the over flow status on 
void overflowOn(){
  status = status | 0x40;
}

//turns the over flow status off
void overflowOff(){
  status = status & 0xBF;
}

//returns the over flow status 
int checkOverflow(){
  int check = (status & 0x40) >> 6;
  return check;
}

//turns the carry status on
void carryOn(){
  status = status | 0x01;
}

//turns the carry status off 
void carryOff(){
  status = status & 0xFE;
}

//returns the carry flag on 
int checkCarry(){
  unsigned char check = (status & 0x1);
  if(check == 1){
    return 1;
  }
  return 0;
}
/*****
 * This instruction adds the contents of a memory location to the accumulator together with the carry bit. If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * Immediate addressing doesn’t strictly deal with memory addresses - this is the mode where actual values are used
 * */
void ADC_immediate(){
    pC++;
    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[pC] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[pC];
      if(signA + signM + buf >=127 | signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[pC] + buf;
      flagADC();
      pC++;
  }

/***
 * All instructions that support absolute addressing (with the exception of the jump instructions) also have the option to take a single-byte address.
 * */
void ADC_zeroPage(){
      pC++;
      
      unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + (result[result[pC]])%256 + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[result[pC]];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[result[pC]] + buf;
      flagADC();
      pC++;
}

/****
 * In this mode, a zero page address is given, and then the value of the X register is added.
 * */
void ADC_zeroPageX(){
  pC++;
  unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + (result[result[pC]+X])%256 + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[result[pC]+X];
      if(signA + signM + buf >=127 | signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[result[pC]+X] + buf;
      flagADC();
      pC++;
}

/****
 * With absolute addressing, the full memory location is used as the argument to the instruction.
 * */

void ADC_absolute(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2;

    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[absolute] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[absolute] + buf;
      flagADC();
      pC++;
  }

  /***
   * These are the absolute addressing versions of zero page,X and zero page,Y
   * 
   * */
  void ADC_absoluteX(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2 + X;

    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[absolute] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[absolute] + buf;

      flagADC();
      pC++;
  }

  /***
   * These are the absolute addressing versions of zero page,X and zero page,Y
   * */
  void ADC_absoluteY(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2 + Y;

    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[absolute] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[absolute] + buf;

      flagADC();
      pC++;
  }

  /**
   * Basically, you take the zero page address, add the value of the X register to it, then use that to look up a two-byte address. For example:
   * */
  void ADC_indirectX(){
    pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;
    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[absolute] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[absolute] + buf;

      flagADC();
      pC++;
  }


  /**
   * Instead of adding the X register to the address before dereferencing, the zero page address is dereferenced, and the Y register is added to the resulting address.
   * 
   * */
  void ADC_indirectY(){
    pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

    unsigned char buf = checkCarry();

    //if A positive and M is positve a
      if(A + result[absolute] + buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA + signM + buf >=127| signA + signM + buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A + result[absolute] + buf;

      flagADC();
      pC++;
  }

/***
 * A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * */

void AND_immediate(){
  pC++;
  A = A & result[pC];
  flagADC();
  pC++;
}

void AND_zeroPage(){
  pC++;
  A = A & result[result[pC]]%256;
  flagADC();
  pC++;
}

void AND_zeroPageX(){
  pC++;
  A = A & result[result[pC]+X]%256;
  flagADC();
  pC++;
}

void AND_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  A = A & result[absolute];
  flagADC();
  pC++;
}

void AND_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  A = A & result[absolute];
  flagADC();
  pC++;
}

void AND_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + Y;

  A = A & result[absolute];
  flagADC();
  pC++;
}

void AND_indirectX(){
  pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

  A = A & result[absolute];
  flagADC();
  pC++;
}

void AND_indirectY(){
  pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

  A = A & result[absolute];
  flagADC();
  pC++;
}

/***
 * This operation shifts all the bits of the accumulator or memory contents one bit left. Bit 0 is set to 0 and bit 7 is placed in the carry flag. The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations), setting the carry if the result will not fit in 8 bits.
 * */
void ASL_accumulator(){
  int bit = A >> 7;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  A = A <<1;
  flagADC();
  pC++;
}

void ASL_zeroPage(){
  pC++;
  int bit = result[result[pC]] >> 7;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }

  result[result[pC]] = result[result[pC]] <<1;
  if(result[result[pC]]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[result[pC]] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ASL_zeroPageX(){
  pC++;
  int bit = result[result[pC]+X] >> 7;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]+X] = result[result[pC]+X] <<1;
  if(result[result[pC]+X]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[result[pC]+X] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ASL_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  int bit = result[absolute] >>7;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute]<<1;

  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[absolute] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ASL_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  int bit = result[absolute] >>7;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  
  result[absolute] = result[absolute]<<1;
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[absolute] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

/**
 * This instructions is used to test if one or more bits are set in a target memory location. The mask pattern in A is ANDed with the value in memory to set or clear the zero flag, but the result is not kept. Bits 7 and 6 of the value from memory are copied into the N and V flags.
 * */

void BIT_zeroPage(){
  pC++;
  unsigned char check = result[result[pC]];
  if(check>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(check << 1 >>7 == 1){
    overflowOn();
  }else{
    overflowOff();
  }

  unsigned hm = check & A;
  if(hm == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void BIT_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  unsigned char check = result[absolute];
  if(check>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(check << 1 >>7 == 1){
    overflowOn();
  }else{
    overflowOff();
  }

  unsigned hm = check & A;
  if(hm == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

/**
 * If the carry flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BCC(){
  pC++;

  signed char m = result[pC];
  if(checkCarry()==0){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/**
 * If the carry flag is set then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BCS(){
  pC++;
  signed char m = result[pC];
  if(checkCarry()==1){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/**
 * If the zero flag is set then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BEQ(){
  pC++;
  signed char m = result[pC];
  if(checkZero()){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/**
 * If the negative flag is set then add the relative displacement to the program counter to cause a branch to a new location.
 * */

void BMI_relative(){
  pC++;
  signed char m = result[pC];
  if(checkNegative()){
  pC = pC+ m;
  }else{
  pC++;
  }
  /**
  if(checkNegative() == 1){
    if(result[pC] >> 7 ==1){
      signed char buf = result[pC];
      pC = pC + buf;
    }else{
    pC = pC + result[pC];
    }
    */
}

/***
 * If the zero flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
 * */

void BNE_relative(){
  pC++;
  signed char m = result[pC];
  if(checkZero()==0){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/***
 * If the negative flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BPL_relative(){
  pC++;
  signed char m = result[pC];
  if(checkNegative()==0){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/**
 * The BRK instruction forces the generation of an interrupt request. The program counter and processor status are pushed on the stack then the IRQ interrupt vector at $FFFE/F is loaded into the PC and the break flag in the status set to one.
 * */

void BRK(){
  pC++;
}

/**8
 * If the overflow flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BVC(){
  pC++;
  signed char m = result[pC];
  if(checkOverflow()==0){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/**
 * If the overflow flag is set then add the relative displacement to the program counter to cause a branch to a new location.
 * */
void BVS(){
  pC++;
  signed char m = result[pC];
  if(checkOverflow()==1){
  pC = pC+ m;
  }else{
  pC++;
  }
}

/***
 * Set the carry flag to zero.
 * */
void CLC(){
  carryOff();
  pC++;
}

/***
 * Sets the decimal mode flag to zero.
 * */

void CLD(){pC++;}

/**
 * Clears the interrupt disable flag allowing normal interrupt requests to be serviced.
 * */
void CLI(){pC++;}

/**
 * Clears the overflow flag.
 * */
void CLV(){
  overflowOff();
  pC++;
}

/**
 * This instruction compares the contents of the accumulator with another memory held value and sets the zero and carry flags as appropriate.
 * */
void CMP_immediate(){
  pC++;
  if(A == result[pC]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[pC])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[pC]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_zeroPage(){
  pC++;
  if(A == result[result[pC]]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[result[pC]])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[result[pC]]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_zeroPageX(){
  pC++;
  if(A == result[result[pC]+X]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[result[pC]+X])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[result[pC]+X]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  if(A == result[absolute]){
   negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[absolute])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2+X;

  if(A == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[absolute])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2+Y;

  if(A == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[absolute])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_indirectX(){
pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

    if(A == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[absolute])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CMP_indirectY(){
pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

    if(A == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((A-result[absolute])>>7 ==0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(A>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

/***
 * This instruction compares the contents of the X register with another memory held value and sets the zero and carry flags as appropriate.
 * */
void CPX_immediate(){
  pC++;
  if(X == result[pC]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((X-result[pC])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(X>result[pC]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CPX_zeroPage(){
  pC++;
  if(X == result[result[pC]]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((X-result[result[pC]])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(X>result[result[pC]]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CPX_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  if(X == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((X-result[absolute])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(X>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

/**
 * This instruction compares the contents of the Y register with another memory held value and sets the zero and carry flags as appropriate.
 * */
void CPY_immediate(){
  pC++;
  if(Y == result[pC]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((Y-result[pC])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(Y>result[pC]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CPY_zeroPage(){
  pC++;
  if(Y == result[result[pC]]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((Y-result[result[pC]])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(Y>result[result[pC]]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

void CPY_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  if(Y == result[absolute]){
    negativeOff();
    carryOn();
    zeroOn();
    return;
  }else{
    zeroOff();
  }
  if((Y-result[absolute])>>7 == 0){
    negativeOff();
  }else{
    negativeOn();
  }
  if(Y>result[absolute]){
    carryOn();
  }else{
    carryOff();
  }
  pC++;
  return;
}

/***
 * Subtracts one from the value held at a specified memory location setting the zero and negative flags as appropriate.
 * */
void DEC_zeroPage(){
  pC++;
  result[result[pC]] = result[result[pC]]-1;
  if(result[result[pC]]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[result[pC]]>>7 == 1){
   negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void DEC_zeroPageX(){
  pC++;
  result[result[pC]+X] = result[result[pC]+X]-1;
  if(result[result[pC]+X]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[result[pC]+X]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void DEC_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  result[absolute] = result[absolute]-1;
  if(result[absolute]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void DEC_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2+X;

  result[absolute] = result[absolute]-1;
  if(result[absolute]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * Subtracts one from the X register setting the zero and negative flags as appropriate.
 * */
void DEX_implied(){
  X = X-1;
  if(X== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * Subtracts one from the Y register setting the zero and negative flags as appropriate.
 * */
void DEY_implied(){
  Y = Y-1;
  if(Y== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * */

void EOR_immediate(){
  pC++;
  A = A ^ result[pC];
  flagADC();
  pC++;
}

void EOR_zeroPage(){
  pC++;
  A = A ^ result[result[pC]]%256;
  flagADC();
  pC++;
}

void EOR_zeroPageX(){
  pC++;
  A = A ^ result[result[pC]+X]%256;
  flagADC();
  pC++;
}

void EOR_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  A = A ^ result[absolute];
  flagADC();
  pC++;
}

void EOR_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  A = A ^ result[absolute];
  flagADC();
  pC++;
}

void EOR_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + Y;

  A = A ^ result[absolute];
  flagADC();
  pC++;
}

void EOR_indirectX(){
  pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

  A = A ^ result[absolute];
  flagADC();
  pC++;
}

void EOR_indirectY(){
  pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

  A = A ^ result[absolute];
  flagADC();
  pC++;
}

/**
 * Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
 * */
void INC_zeroPage(){
  pC++;
  result[result[pC]] = result[result[pC]]+1;
  if(result[result[pC]]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[result[pC]]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void INC_zeroPageX(){
  pC++;
  result[result[pC]+X] = result[result[pC]+X]+1;
  if(result[result[pC]+X]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[result[pC]+X]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void INC_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  result[absolute] = result[absolute]+1;
  if(result[absolute]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void INC_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2+X;

  result[absolute] = result[absolute]+1;
  if(result[absolute]== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * Adds one to the X register setting the zero and negative flags as appropriate.
 * */
void INX_implied(){
  X = X+1;
  if(X== 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/***
 * Adds one to the Y register setting the zero and negative flags as appropriate.
 * */
void INY_implied(){
  Y = Y+1;
  if(Y == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}


/***
 * Sets the program counter to the address specified by the operand.
 * */
void JMP_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  pC = result[absolute];
  
}

void JMP_indirect(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC]<<8;

  int absolute = mask1|mask2;

  pC = result[absolute]+(result[absolute+1]<<8);
}

/***
 * Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate.
 * */
void LDA_immediate(){
  pC++;
  A = result[pC];
  flagADC();
  pC++;
}

void LDA_zeroPage(){
  pC++;
  A = result[result[pC]]%256;
  flagADC();
  pC++;
}

void LDA_zeroPageX(){
  pC++;
  A = result[result[pC]+X]%256;
  flagADC();
  pC++;
}

void LDA_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  A = result[absolute];
  flagADC();
  pC++;
}

void LDA_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  A = result[absolute];
  flagADC();
  pC++;
}

void LDA_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + Y;

  A = result[absolute];
  flagADC();
  pC++;
}

void LDA_indirectX(){
  pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

  A = result[absolute];
  flagADC();
  pC++;
}

void LDA_indirectY(){
  pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

  A = result[absolute];
  flagADC();
  pC++;
}

/**
 * Loads a byte of memory into the X setting the zero and negative flags as appropriate.
 * */
void LDX_immediate(){
  pC++;
  X = result[pC];
  if(X ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDX_zeroPage(){
  pC++;
  X = result[result[pC]]%256;
  if(X ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDX_zeroPageY(){
  pC++;
  X = result[result[pC]+Y]%256;
  if(X ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDX_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  X = result[absolute];
  if(X ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDX_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + Y;

  X = result[absolute];
  if(X ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * Loads a byte of memory into the Y register setting the zero and negative flags as appropriate.
 * */
void LDY_immediate(){
  pC++;
  Y = result[pC];
  if(Y ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDY_zeroPage(){
  pC++;
  Y = result[result[pC]]%256;
  if(Y ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDY_zeroPageX(){
  pC++;
  Y = result[result[pC]+X]%256;
  if(Y ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDY_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  Y = result[absolute];
  if(Y ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

void LDY_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  Y = result[absolute];
  if(Y ==0 ){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/***
 * Each of the bits in A or M is shift one place to the right. The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
 * */

void LSR_accumulator(){
  int bit = A & 1;
  if(bit ==1){
    carryOn();
  }else{
    carryOff();
  }
  A = A >>1;
  flagADC();
  pC++;
}

void LSR_zeroPage(){
  pC++;
  int bit = result[result[pC]] & 1;
  if(bit ==1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]] = result[result[pC]] >>1;
  if(result[result[pC]]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[result[pC]] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void LSR_zeroPageX(){
  pC++;
  int bit = result[result[pC]+X] & 1;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]+X] = result[result[pC]+X] >>1;
  if(result[result[pC]+X]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[result[pC]+X] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void LSR_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  int bit = result[absolute] &1;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute]>>1;

  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[absolute] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void LSR_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  int bit = result[absolute] & 1;
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute]>>1;
  if(result[absolute]>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  if(result[absolute] == 0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

/***
 * The NOP instruction causes no changes to the processor other than the normal incrementing of the program counter to the next instruction.
 * */
void NOP(){
  pC++;
}

/***
 * An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * */
void ORA_immediate(){
  pC++;
  A = A | result[pC];
  flagADC();
  pC++;

}

void ORA_zeroPage(){
  pC++;
  A = A | result[result[pC]]%256;
  flagADC();
  pC++;
}

void ORA_zeroPageX(){
  pC++;
  A = A | result[result[pC]+X]%256;
  flagADC();
  pC++;
}

void ORA_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  A = A | result[absolute];
  flagADC();
  pC++;
}

void ORA_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  A = A | result[absolute];
  flagADC();
  pC++;
}

void ORA_absoluteY(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + Y;

  A = A | result[absolute];
  flagADC();
  pC++;
}

void ORA_indirectX(){
  pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

  A = A | result[absolute];
  flagADC();
  pC++;
}

void ORA_indirectY(){
  pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

  A = A | result[absolute];
  flagADC();
  pC++;
}

/***
 * Pushes a copy of the accumulator on to the stack
 * */
void PHA(){
  result[sP] = A;
  sP = sP -1;
  pC++;
}

/**
 * The JSR instruction pushes the address (minus one) of the return point on to the stack and then sets the program counter to the target memory address.
 * */
void JSR(){
  int buf =  pC+3;
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;
  
  unsigned char highBits = buf>>8;
  result[sP] = highBits;
  sP = sP -1;
  unsigned char lowBits = buf&0x00FF;
  result[sP] = lowBits;
  sP = sP-1;

  pC = absolute;
}

/***
 * Pushes a copy of the status flags on to the stack.
 * */
void PHP(){
  result[sP] = status;
  sP = sP - 1;
  pC++;
}

/**
 * Pulls an 8 bit value from the stack and into the accumulator. The zero and negative flags are set as appropriate.
 * */
void PLA(){
  A = result[sP];
  sP = sP+1;
  flagADC();
  pC++;
}

/***
 * Pulls an 8 bit value from the stack and into the processor flags. The flags will take on new states as determined by the value pulled.
 * */

void PLP(){
  status = result[sP];
  sP = sP +1;
  pC++;
}

/**
 * Move each of the bits in either A or M one place to the left. Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
 * */
void ROL_accumulator(){
  unsigned char bit = A>>7;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  A = A << 1;
  if(carry == 1){
    A = A | 0x1;
  }else{
    A = A & 0xFE;
  }
  if(A==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROL_zeroPage(){
  unsigned char bit = result[result[pC]]%256>>7;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]] = result[result[pC]] << 1;
  if(carry == 1){
    result[result[pC]] = result[result[pC]] | 0x1;
  }else{
    result[result[pC]] = result[result[pC]] & 0xFE;
  }
  if(result[result[pC]]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROL_zeroPageX(){
  unsigned char bit = result[result[pC]+X]%256>>7;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]+X] = result[result[pC]+X] << 1;
  if(carry == 1){
    result[result[pC]+X] = result[result[pC]+X] | 0x1;
  }else{
    result[result[pC]+X] = result[result[pC]+X] & 0xFE;
  }
  if(result[result[pC]+X]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROL_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  unsigned char bit = result[absolute]>>7;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute] << 1;
  if(carry == 1){
    result[absolute] = result[absolute] | 0x1;
  }else{
    result[absolute] = result[absolute] & 0xFE;
  }
  if(result[absolute]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROL_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2 + X;

  unsigned char bit = result[absolute]>>7;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute] << 1;
  if(carry == 1){
    result[absolute] = result[absolute] | 0x1;
  }else{
    result[absolute] = result[absolute] & 0xFE;
  }
  if(result[absolute]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

/**
 * Move each of the bits in either A or M one place to the right. Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new carry flag value.
 * */
void ROR_accumulator(){
  unsigned char bit = A & 1;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  A = A >> 1;
  if(carry == 1){
    A = A | 0x80;
  }else{
    A = A & 0x7F;
  }
  if(A==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROR_zeroPage(){
  unsigned char bit = result[result[pC]]%256 & 1;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]] = result[result[pC]] >> 1;
  if(carry == 1){
    result[result[pC]] = result[result[pC]] | 0x80;
  }else{
    result[result[pC]] = result[result[pC]] & 0x7F;
  }
  if(result[result[pC]]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROR_zeroPageX(){
  unsigned char bit = result[result[pC]+X]%256 & 1;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[result[pC]+X] = result[result[pC]+X] >> 1;
  if(carry == 1){
    result[result[pC]+X] = result[result[pC]+X] | 0x80;
  }else{
    result[result[pC]+X] = result[result[pC]+X] & 0x7F;
  }
  if(result[result[pC]+X]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROR_absolute(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2;

  unsigned char bit = result[absolute] & 1;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute] >> 1;
  if(carry == 1){
    result[absolute] = result[absolute] | 0x80;
  }else{
    result[absolute] = result[absolute] & 0x7F;
  }
  if(result[absolute]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

void ROR_absoluteX(){
  pC++;
  int mask1 = result[pC];
  pC++;
  int mask2 = result[pC] << 8;
  int absolute = mask1|mask2+X;

  unsigned char bit = result[absolute] & 1;
  unsigned char carry = checkCarry();
  if(bit == 1){
    carryOn();
  }else{
    carryOff();
  }
  result[absolute] = result[absolute] >> 1;
  if(carry == 1){
    result[absolute] = result[absolute] | 0x80;
  }else{
    result[absolute] = result[absolute] & 0x7F;
  }
  if(result[absolute]==0){
    zeroOn();
  }else{
    zeroOff();
  }
  pC++;
}

/***
 * The RTI instruction is used at the end of an interrupt processing routine. It pulls the processor flags from the stack followed by the program counter.
 * */
void RTI(){pC++;}

/**
 * The RTS instruction is used at the end of a subroutine to return to the calling routine. It pulls the program counter (minus one) from the stack.
 * */
void RTS(){
  int mask1 = result[sP];
  sP = sP-1;
  int mask2 = result[sP] <<8;
  sP = sP-1;
  int adress = mask1|mask2+1;

  pC = adress;
}

/***
 * This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit. If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
 * */
void SBC_immediate(){
    pC++;
    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[pC] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[pC];
      if(signA - signM - buf >=127 | signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[pC] - buf;
      flagADC();
      pC++;
  }

void SBC_zeroPage(){
      pC++;
      unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - (result[result[pC]])%256 - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[result[pC]];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[result[pC]] - buf;

      flagADC();
      pC++;
}

void SBC_zeroPageX(){
  pC++;
  unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - (result[result[pC]+X])%256 - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[result[pC]+X];
      if(signA - signM - buf >=127 | signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[result[pC]+X] - buf;
      flagADC();
      pC++;
}

void SBC_absolute(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2;

    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[absolute] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[absolute] - buf;
      flagADC();
      pC++;
  }

  void SBC_absoluteX(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2 + X;

    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[absolute] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[absolute] - buf;

      flagADC();
      pC++;
  }

  void SBC_absoluteY(){
    pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2 + Y;

    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[absolute] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[absolute] - buf;
      flagADC();
      pC++;
  }

  void SBC_indirectX(){
    pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;

    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[absolute] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[absolute] - buf;
      flagADC();
      pC++;
  }

  void SBC_indirectY(){
    pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;

    unsigned char buf = ~checkCarry();

    //if A positive and M is positve a
      if(A - result[absolute] - buf> 256){
        carryOn();
      }else{
        carryOff();
      }
      char signA = A;
      char signM = result[absolute];
      if(signA - signM - buf >=127| signA - signM - buf<-128){
        overflowOn();
      }else{
        overflowOff();
      }
      A = A - result[absolute] - buf;
      flagADC();
      pC++;
  }

/**
 * Set the carry flag to one.
 * */
void SEC(){
  carryOn();
  pC++;
}

/**
 * Set the decimal mode flag to one.
 * */
void SED(){
  pC++;
}

/**
 * Set the interrupt disable flag to one.
 * */
void SEI(){
  pC++;
}

/**
 * Stores the contents of the accumulator into memory.
 * */
void STA_zeroPage(){
  pC++;
  result[result[pC]] = A;
  pC++;
}

void STA_zeroPageX(){
  pC++;
  (result[result[pC]+X]) = A;
  pC++;
}

void STA_absolute(){
  pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2;
    result[absolute] = A;
    pC++;
}

void STA_absoluteX(){
  pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2+X;
    result[absolute] = A;
    pC++;
}

void STA_absoluteY(){
  pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2+Y;
    result[absolute] = A;
    pC++;
}

void STA_indirectX(){
  pC++;
    int mask1 = result[pC]+X;
    int mask2 = result[mask1+1]<<8;

    int absolute = mask1|mask2;
  result[absolute] = A;
  pC++;
}

void STA_indirectY(){
  pC++;
    int mask1 = result[pC];
    int mask2 = (result[pC+1]<<8)+Y;

    int absolute = mask1|mask2;
  result[absolute] = A;
  pC++;
}

/**
 * Stores the contents of the X register into memory.
 * */
void STX_zeroPage(){
  pC++;
  (result[result[pC]]) = X;
  pC++;
}

void STX_zeroPageY(){
  pC++;
  (result[result[pC]+Y]) = X;
  pC++;
}

void STX_absolute(){
  pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2;
    result[absolute] = X;
    pC++;
}

/**
 * Stores the contents of the Y register into memory.
 * */
void STY_zeroPage(){
  pC++;
  (result[result[pC]]) = Y;
  pC++;
}

void STY_zeroPageX(){
  pC++;
  (result[result[pC]+X]) = Y;
  pC++;
}

void STY_absolute(){
  pC++;
    int mask1 = result[pC];
    pC++;
    int mask2 = result[pC] << 8;

    int absolute = mask1|mask2;
    result[absolute] = Y;
    pC++;
}

/**
 * Copies the current contents of the accumulator into the X register and sets the zero and negative flags as appropriate.
 * */
void TAX(){
  X= A;
  if(X==0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}
    
    /**
     * Copies the current contents of the accumulator into the Y register and sets the zero and negative flags as appropriate.
     * */
  void TAY(){
    Y = A;
    if(Y==0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(Y>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/***
 * Copies the current contents of the stack register into the X register and sets the zero and negative flags as appropriate.
 * */
void TSX(){
    X = sP;
    if(X==0){
    zeroOn();
  }else{
    zeroOff();
  }
  if(X>>7 == 1){
    negativeOn();
  }else{
    negativeOff();
  }
  pC++;
}

/**
 * Copies the current contents of the X register into the accumulator and sets the zero and negative flags as appropriate.
 * */
void TXA(){
    A = X;
    flagADC();
    pC++;
}

/**
 * Copies the current contents of the X register into the stack register
 * */
void TXS(){
  sP = X;
  pC++;
}

/**
 * Copies the current contents of the Y register into the accumulator and sets the zero and negative flags as appropriate.
 * */
void TYA(){
  A = Y;
  flagADC();
  pC++;
}

//points to the currect opCode
void readOpCode(int index){
    opCode[index]();
}
