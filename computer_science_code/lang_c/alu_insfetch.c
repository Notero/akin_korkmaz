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
    if (PC >= 65536){
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
    if (*instruction == 00000000) {
        return 1;
    }
    
    //return not halt
    return 0;
}
