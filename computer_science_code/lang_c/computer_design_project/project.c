#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    //ALUControl will be rangin from 0 to 7
    switch (ALUControl) {
        case 0: //add case
            *ALUresult = A + B;
            break;
        case 1: // sub case
            *ALUresult = A - B;
            break;
        case 2: // less than case (signed)
            
            if ((signed)A < (signed)B)
                *ALUresult = 1;
            else
                *ALUresult = 0;
            
            break;
        case 3: //less than case (unsigned)
            if (A < B)
                *ALUresult = 1;
            else
                *ALUresult = 0;
            break;
        case 4: // and case
            *ALUresult = A & B;
            break;
        case 5: // or case
            *ALUresult = A | B;
            break;
        case 6: //shift 16 left case
            *ALUresult = B << 16;
            break;
        case 7: // Not A case
            *ALUresult = ~A;
            break;
        default: //unknown command case
            return;
    }
    //checks if result is 0 or not
    if (*ALUresult == 0)
        *Zero = 1;
    else
        *Zero = 0;

    
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //check if out of bounds MEMSIZE from spimcore.c 64KB
    //halt cond 1
    if (PC >= 65536 || PC < 0){
        return 1;
    }
    
    //checks if PC is a multiple of 4
    //halt cond 2
    if (PC % 4 != 0) {
        return 1;
    }
    
    //gets the instrutions from mem array
    *instruction = Mem[PC / 4];
    
    //checks if instructions 0x00000000 from project instructions
    if (*instruction == 0x00000000) {
        return 1;
    }
    
    //return not halt
    return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

    //Initialize masks to select desired bits
    unsigned opMask =     0b11111100000000000000000000000000; //6 Bits from [31-26]
    unsigned r1Mask =     0b00000011111000000000000000000000; //5 Bits from [25-21]
    unsigned r2Mask =     0b00000000000111110000000000000000; //5 Bits from [20-16]
    unsigned r3Mask =     0b00000000000000001111100000000000; //5 Bits from [15-11]
    unsigned functMask =  0b00000000000000000000000000111111; //6 Bits from [5-0]
    unsigned offsetMask = 0b00000000000000001111111111111111; //16 Bits from [15-0]
    unsigned jsecMask =   0b00000011111111111111111111111111; //26 Bits from [25-0]

    //Perform bitwise and using masks to isolate desired bits
    unsigned opTemp = instruction & opMask;
    unsigned r1Temp = instruction & r1Mask;
    unsigned r2Temp = instruction & r2Mask;
    unsigned r3Temp = instruction & r3Mask;
    unsigned functTemp = instruction & functMask;
    unsigned offsetTemp = instruction & offsetMask;
    unsigned jsecTemp = instruction & jsecMask;

    //Shift right to eliminate unecessary bits, output to provided addresses
    *op = opTemp >> 26;
    *r1 = r1Temp >> 21;
    *r2 = r2Temp >> 16;
    *r3 = r3Temp >> 11;
    *funct = functTemp >> 0;
    *offset = offsetTemp >> 0;
    *jsec = jsecTemp >> 0;

}


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

/*
List of Instructions from Appendix A: Figure 1 from Project Guidlines
Instruction               Opcode (6 bits)
-----------------------------------------
ADD     000000
SUB     000000
AND     000000
OR      000000
SLT     000000
SLTU    000000
ADDI    001000
LW      100011
SW      101011
LUI     001111
BEQ     000100
SLTI    001010
SLTIU   001011
J       000010
*/

    if(op==0b000000) { //All R-Type functions (add through sltu)

        controls->RegDst = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b111;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 1;
  
    } else if(op==0b000010) { //Jump

        controls->RegDst = 2;
        controls->Jump = 1;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 0b000;
        controls->MemWrite = 0;
        controls->ALUSrc = 2;
        controls->RegWrite = 0;
  
    } else if(op==0b000100) { //branch on equal (BEQ)

        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 1;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 0b001;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 0;
  
    } else if(op==0b001000) { //add immediate (addi)

        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b000;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
  
    } else if(op==0b001010) { //set less than immediate (SLTI)

        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b010;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;

    } else if(op==0b001011) { //set less than immediate unsigned (SLTIU)

        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b011;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
  
    } else if(op==0b001111) { //load upper immediate (LUI)

        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b110;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
  
    } else if(op==0b100011) { //load word (LW)

        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->ALUOp = 0b000;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
  
    } else if(op==0b101011) { //store word (SW)

        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0b000;
        controls->MemWrite = 1;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
  
    } else { //Invalid Instruction
        return 1; //Halt
    }

    return 0;
  
//What other possible inputs?
//I have no idea, I think these 9 options cover every OPCODE for the 14 provided instructions
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2){
    // Read data from registers based on register numbers r1 and r2
    *data1 = Reg[r1]; // Data from register r1
    *data2 = Reg[r2]; // Data from register r2
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value){
    // Sign extend the offset value to 32 bits
    int ones = 0xffff << 16; // Create a mask of ones in the upper 16 bits
    *extended_value = (offset >> 15 ? offset | ones : offset); // If the offset is negative, sign extend
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero) {
    unsigned operand2 = (ALUSrc == 1) ? extended_value : data2;
    char ALUControl;

    // Determine ALUControl based on ALUOp and funct
    switch (ALUOp) {
        case 0: ALUControl = 0; break; // Addition
        case 1: ALUControl = 1; break; // Subtraction
        case 2: // R-type operation
            switch (funct) {
                case 32: ALUControl = 0; break; // add
                case 34: ALUControl = 1; break; // subtract
                case 42: ALUControl = 2; break; // set on less than
                case 43: ALUControl = 3; break; // set on less than (unsigned)
                case 36: ALUControl = 4; break; // and
                case 37: ALUControl = 5; break; // or
                default: return 1; // Halt on illegal instruction
            }
            break;
        default: return 1; // Halt on illegal instruction
    }

    // Performing the ALU operation
    ALU(data1, operand2, ALUControl, ALUresult, Zero);

    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem) {
    
    if (ALUresult % 4 != 0 || ALUresult < 0 || ALUresult >= 65536) {
        // Check if address is not word-aligned or out of bounds
        return 1; // Halt
    }
    if (MemRead == 1) {
        *memdata = Mem[ALUresult / 4]; // Reading the memory
    }
    if (MemWrite == 1) {
        Mem[ALUresult / 4] = data2; // Writing the memory
    }
    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst, char MemtoReg, unsigned* Reg) {
    //will exit if register is disabled
    if (RegWrite == 0) {
        return;
    }
    //prevent $zero to register
    if (RegDst == 0 && r2 == 0) {
        return;
    }
    if (RegDst == 1 && r3 == 0) {
        return;
    }
    //writes the memory data to r2 for i-type
    if (MemtoReg == 1 && RegDst == 0) {
        Reg[r2] = memdata;
    }
    //Writes ALU result to r3 for r-type
    else if (MemtoReg == 0 && RegDst == 1) {
        Reg[r3] = ALUresult;
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC) {
    //+4 to PC
    *PC += 4;

    //sets PC to jump while maintaining upper 4 bits
    if (Jump) {
        *PC = (*PC & 0xF0000000) | (jsec << 2);
    }

    //updates PC if Branch and Zero are enabled
    if (Branch && Zero) {
        *PC += (extended_value << 2);
    }
}


